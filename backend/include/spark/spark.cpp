/*
 * Author: Paul Contreras
 * File: spark.cpp
 * GitHub: @pol-cova
 * Description:
 * Swift and Protected Authentication Resource Kit
 */

#include "spark.h"

// Function to generate a random salt string
string generate_salt()
{
    // Define the character set from which the salt will be generated
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // Length of the salt
    const int len = 16;
    // Initialize an empty string to hold the salt
    string salt;
    // Reserve memory for the salt to avoid reallocations
    salt.reserve(len);
    // Initialize a random device for seeding the random number generator
    random_device rd;
    // Initialize the Mersenne Twister pseudo-random number generator with a seed from random_device
    mt19937 gen(rd());

    // Define a uniform distribution to generate random indices into the charset
    uniform_int_distribution<int> distribution(0, charset.size() - 1);
    
    // Loop to generate each character of the salt
    for (int i = 0; i < len; i++)
    {
        // Append a random character from the charset to the salt string
        salt += charset[distribution(gen)];
    }

    // Return the generated salt
    return salt;
}


string hashPassword(const string password, const string salt) {
    // Concatenate password and salt
    string data = password + salt;

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
    stringstream ss;
    for (int i = 0; i < hash_len; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
// Function to validate a password against a hash with salt
bool validatePassword(const string password, const string storedHash, const string storedSalt) {
    string inputHash = hashPassword(password, storedSalt);
    return inputHash == storedHash;
}

// Function to generate a JWT token
string generateJWT(const string username, const string role, const string userID) {
    // Create a new JWT builder
    auto token = jwt::create()
            .set_type("JWS")
            .set_issuer("authSpark-v1")
            .set_issued_at(std::chrono::system_clock::now());

    // Create claim objects for the payload
    jwt::claim username_claim = jwt::claim(username);
    jwt::claim role_claim = jwt::claim(role);
    jwt::claim userID_claim = jwt::claim(userID);

    // Add payload claims to the token
    token.set_payload_claim("username", username_claim)
            .set_payload_claim("role", role_claim)
            .set_payload_claim("userID", userID_claim);

    // Set expiration time to 1 hour from now
    auto expiration_time = std::chrono::system_clock::now() + std::chrono::hours(1);
    token.set_expires_at(expiration_time);

    // Sign the token with the HS256 algorithm and the secret "secret"
    return token.sign(jwt::algorithm::hs256("secret"));
}