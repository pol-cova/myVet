import React from "react";
import { Button, Checkbox, Label, TextInput } from "flowbite-react";
import { FaUserAstronaut, FaLock } from "react-icons/fa";

function Signup() {
  return (
    <section class="bg-gray-50 dark:bg-gray-900">
      <div class="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0">
        <a
          href="#"
          class="flex items-center mb-6 text-2xl font-semibold text-gray-900 dark:text-white"
        >
          <img class="w-8 h-8 mr-2" src="src/assets/bxs-dog.svg" alt="logo" />
          myVet System
        </a>
        <div class="w-full bg-white rounded-lg shadow dark:border md:mt-0 sm:max-w-md xl:p-0 dark:bg-gray-800 dark:border-gray-700">
          <div class="p-6 space-y-4 md:space-y-6 sm:p-8">
            <h1 class="text-xl font-bold leading-tight tracking-tight text-gray-900 md:text-2xl dark:text-white">
              Crea una cuenta
            </h1>
            <form class="space-y-4 md:space-y-6" action="#">
              <div className="mb-2 block">
                <Label htmlFor="username" value="Username" />
              </div>
              <TextInput
                id="username"
                placeholder="JohnDoe"
                addon="@"
                required
                rightIcon={FaUserAstronaut}
              />
              <div className="mb-2 block">
                <Label htmlFor="password" value="Password" />
              </div>
                <TextInput
                    id="password"
                    type="password"
                    placeholder="********"
                    required
                    rightIcon={FaLock}
                />
              <div class="flex items-center justify-between">
                <div class="flex items-start">
                  <div class="flex items-center h-5">
                    <input
                      id="remember"
                      aria-describedby="remember"
                      type="checkbox"
                      class="w-4 h-4 border border-gray-300 rounded bg-gray-50 focus:ring-3 focus:ring-primary-300 dark:bg-gray-700 dark:border-gray-600 dark:focus:ring-primary-600 dark:ring-offset-gray-800"
                      required=""
                    />
                  </div>
                  <div class="ml-3 text-sm">
                    <label
                      for="remember"
                      class="text-gray-500 dark:text-gray-300"
                    >
                      Recuérdame
                    </label>
                  </div>
                </div>
                <a
                  href="#"
                  class="text-sm font-medium text-primary-600 hover:underline dark:text-primary-500"
                >
                    Olvidaste tu contraseña?
                </a>
              </div>
              <Button type="submit" style={{ backgroundColor: "#386641" }} >Iniciar sesión</Button>
              <p class="text-sm font-light text-gray-500 dark:text-gray-400">
                Ya tienes cuenta?{" "}
                <a
                  href="/login"
                  class="font-medium text-primary-600 hover:underline dark:text-primary-500"
                >
                  Inicia sesión ahora
                </a>
              </p>
            </form>
          </div>
        </div>
      </div>
    </section>
  );
}

export default Signup;
