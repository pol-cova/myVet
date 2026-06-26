/*
 * Author: Paul Contreras
 * File: spark.cpp
 * GitHub: @pol-cova
 * Description:
 * Swift and Protected Authentication Resource Kit
 */

#include "spark.h"

// Function to generate a random salt string
std::string generate_salt()
{
    // Define the character set from which the salt will be generated
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // Length of the salt
    const int len = 16;
    // Initialize an empty string to hold the salt
    std::string salt;
    // Reserve memory for the salt to avoid reallocations
    salt.reserve(len);
    // Initialize a random device for seeding the random number generator
    std::random_device rd;
    // Initialize the Mersenne Twister pseudo-random number generator with a seed from random_device
    std::mt19937 gen(rd());

    // Define a uniform distribution to generate random indices into the charset
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(charset.size() - 1));
    
    // Loop to generate each character of the salt
    for (int i = 0; i < len; i++)
    {
        // Append a random character from the charset to the salt string
        salt += charset[distribution(gen)];
    }

    // Return the generated salt
    return salt;
}

std::string hashPassword(const std::string password, const std::string salt) {
    // Concatenate password and salt
    std::string data = password + salt;

    // Create a new digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    // Initialize the digest context for SHA-256
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // Update the digest context with the data
    EVP_DigestUpdate(mdctx, data.c_str(), data.length());

    // Finalize the digest and obtain the hash
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // Clean up the digest context
    EVP_MD_CTX_free(mdctx);

    // Convert the hash to a hexadecimal string
    std::stringstream ss;
    for (unsigned int i = 0; i < hash_len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// Constant-time string comparison to prevent timing attacks
bool constantTimeCompare(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        return false;
    }
    volatile char result = 0;
    for (size_t i = 0; i < a.length(); ++i) {
        result |= (a[i] ^ b[i]);
    }
    return result == 0;
}

// Function to validate a password against a hash with salt
bool validatePassword(const std::string password, const std::string storedHash, const std::string storedSalt) {
    std::string inputHash = hashPassword(password, storedSalt);
    return constantTimeCompare(inputHash, storedHash);
}

// Function to generate a JWT token
std::string generateJWT(const std::string username, const std::string role, const std::string userID, const std::string mail) {
    // Create a new JWT builder
    auto token = jwt::create()
            .set_type("JWS")
            .set_issuer("authSpark-v1")
            .set_issued_at(std::chrono::system_clock::now());

    // Create claim objects for the payload
    jwt::claim username_claim = jwt::claim(username);
    jwt::claim role_claim = jwt::claim(role);
    jwt::claim userID_claim = jwt::claim(userID);
    jwt::claim mail_claim = jwt::claim(mail);

    // Add payload claims to the token
    token.set_payload_claim("username", username_claim)
            .set_payload_claim("role", role_claim)
            .set_payload_claim("userID", userID_claim)
            .set_payload_claim("mail", mail_claim);

    // Set expiration time to 1 hour from now
    auto expiration_time = std::chrono::system_clock::now() + std::chrono::hours(1);
    token.set_expires_at(expiration_time);

    // Get secret dynamically
    const char* env_secret = std::getenv("JWT_SECRET");
    if (!env_secret || std::string(env_secret).empty()) {
        std::cerr << "FATAL: JWT_SECRET environment variable is not set!" << std::endl;
        throw std::runtime_error("JWT_SECRET environment variable is required.");
    }
    std::string secret = env_secret;

    // Sign the token with the HS256 algorithm
    return token.sign(jwt::algorithm::hs256(secret));
}

// Function to verify a JWT token and extract claims
bool verifyJWT(const std::string& token_str, std::string& username, std::string& role, std::string& userID, std::string& mail) {
    try {
        if (token_str.empty()) {
            return false;
        }
        auto decoded = jwt::decode(token_str);
        
        // Get secret dynamically
        const char* env_secret = std::getenv("JWT_SECRET");
        if (!env_secret || std::string(env_secret).empty()) {
            std::cerr << "FATAL: JWT_SECRET environment variable is not set!" << std::endl;
            throw std::runtime_error("JWT_SECRET environment variable is required.");
        }
        std::string secret = env_secret;
        
        auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256(secret))
                .with_issuer("authSpark-v1");
        
        verifier.verify(decoded);
        
        if (decoded.has_payload_claim("username")) {
            username = decoded.get_payload_claim("username").as_string();
        }
        if (decoded.has_payload_claim("role")) {
            role = decoded.get_payload_claim("role").as_string();
        }
        if (decoded.has_payload_claim("userID")) {
            userID = decoded.get_payload_claim("userID").as_string();
        }
        if (decoded.has_payload_claim("mail")) {
            mail = decoded.get_payload_claim("mail").as_string();
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "JWT verification error: " << e.what() << std::endl;
        return false;
    }
}