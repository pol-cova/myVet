/*
 * Author: Paul Contreras
 * File: spark.h
 * GitHub: @pol-cova
 * Description:
 * Swift and Protected Authentication Resource Kit
 */

#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <random>
#include <iomanip>
#include <sstream>
#include <jwt-cpp/jwt.h>
using namespace std;


// Function to generate a random salt string
string generate_salt();
// Function to hash a password with a salt
string hashPassword(const string password, const string salt);
// Function to validate a password against a hash with salt
bool validatePassword(const string password, const string storedHash, const string storedSalt);
// Function to generate a JWT token
string generateJWT(const string username, const string role, const int userID, const string mail);

