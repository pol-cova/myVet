import { Button, Checkbox, Label, TextInput } from "flowbite-react";
import { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";
import { FaLock } from "react-icons/fa";

// Navbar
import NavMenu from "../components/Navbar";

function LoginView() {
  const navigate = useNavigate();
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");

  const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    try {
      const response = await axios.post("http://127.0.0.1:18080/auth/login", {
        username,
        password,
      });
      if (response.data.status === 'OK') {
        // Store the token in local storage
        localStorage.setItem('token', response.data.token);
        console.log('User logged in successfully');
        // Redirect to the home page
        navigate('/home');
      }
    } catch (error) {
        if (axios.isAxiosError(error) && error.response?.status === 401) {
            alert('Usuario y/o Contraseña incorrecta' );
          } else {
            console.error(error);
          }
    }
    // set the username and password to empty strings
    setUsername("");
    setPassword("");
  };

  return (
    <>
    <NavMenu />
      <section className="bg-gray-50 dark:bg-gray-900">
        <div className="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0">
          <a
            href="/"
            className="flex items-center mb-6 text-2xl font-semibold text-gray-900 dark:text-white"
          >
            <img
              className="w-8 h-8 mr-2"
              src="./src/assets/bxs-dog.svg"
              alt="logo"
            />
            MyVet
          </a>
          <div className="w-full bg-white rounded-lg shadow dark:border md:mt-0 sm:max-w-md xl:p-0 dark:bg-gray-800 dark:border-gray-700">
            <div className="p-6 space-y-4 md:space-y-6 sm:p-8">
              <h1 className="text-xl font-bold leading-tight tracking-tight text-gray-900 md:text-2xl dark:text-white">
                Ingresa en tu cuenta
              </h1>
              <form className="flex max-w-md flex-col gap-4" onSubmit={handleSubmit}>
                <div>
                  <div className="mb-2 block">
                    <Label htmlFor="username" value="Usuario" />
                  </div>
                  <TextInput
                    id="username"
                    type="text"
                    placeholder="username"
                    required
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                    addon="@"
                  />
                </div>
                <div>
                  <div className="mb-2 block">
                    <Label htmlFor="password1" value="Tu contraseña" />
                  </div>
                  <TextInput
                    id="password1"
                    type="password"
                    placeholder="* * * * * * *"
                    required
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                    rightIcon={FaLock}
                  />
                </div>
                <div className="flex items-center gap-2">
                  <Checkbox id="remember" />
                  <Label htmlFor="remember">Recordarme</Label>
                </div>
                <Button type="submit" style={{ backgroundColor: "#386641" }}>
                  Entrar
                </Button>
              </form>
              <p className="text-gray-500 dark:text-gray-300">Si no tienes cuenta. <a href="/register" className="ml-1 font-medium text-cyan-600 hover:underline dark:text-cyan-500">Regístrate, es gratis</a> </p>
            </div>
          </div>
        </div>
      </section>
    </>
  );
}

export default LoginView;
