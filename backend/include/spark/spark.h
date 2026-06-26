/*
 * Author: Paul Contreras
 * File: spark.h
 * GitHub: @pol-cova
 * Description:
 * Swift and Protected Authentication Resource Kit
 */

#ifndef SPARK_AUTH_H
#define SPARK_AUTH_H

#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <random>
#include <iomanip>
#include <sstream>
#include <jwt-cpp/jwt.h>

// Function to generate a random salt string
std::string generate_salt();
// Function to hash a password with a salt
std::string hashPassword(const std::string password, const std::string salt);
// Function to validate a password against a hash with salt
bool validatePassword(const std::string password, const std::string storedHash, const std::string storedSalt);
// Function to generate a JWT token
std::string generateJWT(const std::string username, const std::string role, const std::string userID, const std::string mail);
// Function to verify a JWT token and extract claims
bool verifyJWT(const std::string& token_str, std::string& username, std::string& role, std::string& userID, std::string& mail);

#endif // SPARK_AUTH_H
