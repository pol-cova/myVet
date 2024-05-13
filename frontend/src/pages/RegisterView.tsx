import { Button, Checkbox, Label, TextInput } from "flowbite-react";
import { useState } from "react";
import { useNavigate } from "react-router-dom";
import axios from "axios";
import { FaLock } from "react-icons/fa";
import { HiMail, HiPhone } from "react-icons/hi";
import { FaUserAstronaut } from "react-icons/fa";


// Navbar
import NavMenu from "../components/Navbar";

function RegisterView() {
  const navigate = useNavigate();
  const [user, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [name, setName] = useState("");
  const [mail, setMail] = useState("");
  const [phone, setPhone] = useState("");

  const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/auth/register",
        {
          user,
          password,
          name,
          mail,
          phone,
        }
      );
      if (response.data.status === "success") {
        console.log("User registered successfully");
        // Redirect to the home page
        navigate("/login");
      }
    } catch (error) {
      console.error(error);
      alert("Error al registrar el usuario");
    }
    // set the username and password to empty strings
    setUsername("");
    setPassword("");
    setName("");
    setMail("");
    setPhone("");
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
                Regístrate en MyVet
              </h1>
              <form className="flex flex-col gap-4" onSubmit={handleSubmit}>
                <div className="flex flex-row gap-4">
                  <div className="flex-1">
                    <Label htmlFor="username" value="Usuario" />
                    <TextInput
                      id="username"
                      type="text"
                      placeholder="username"
                      required
                      value={user}
                      onChange={(e) => setUsername(e.target.value)}
                      addon="@"

                    />
                  </div>
                  <div className="flex-1">
                    <Label htmlFor="name" value="Nombre" />
                    <TextInput
                      id="name"
                      type="text"
                      placeholder="John Doe"
                      required
                      value={name}
                      onChange={(e) => setName(e.target.value)}
                        rightIcon={FaUserAstronaut}
                
                    />
                  </div>
                </div>
                <div className="flex flex-row gap-4">
                  <div className="flex-1">
                    <Label htmlFor="mail" value="Correo" />
                    <TextInput
                      id="mail"
                      type="email"
                      placeholder="example@mail.com"
                        required
                        value={mail}
                        onChange={(e) => setMail(e.target.value)}
                        rightIcon={HiMail}
                    />
                  </div>
                  <div className="flex-1">
                    <Label htmlFor="phone" value="Teléfono" />
                    <TextInput
                      id="phone"
                      type="tel"
                      placeholder="1234567890"
                      value={phone}
                      onChange={(e) => setPhone(e.target.value)}
                        rightIcon={HiPhone}
                        required
                    />
                  </div>
                </div>
                <div>
                  <Label htmlFor="password1" value="Tu contraseña" />
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
        <Checkbox id="agree" />
        <Label htmlFor="agree" className="flex">
         Acepto&nbsp;
          <a href="#" className="text-cyan-600 hover:underline dark:text-cyan-500">
            los términos y condiciones
          </a>
        </Label>
      </div>
                <Button type="submit" style={{ backgroundColor: "#386641" }}>
                  Crear cuenta
                </Button>
              </form>
              <p className="text-gray-500 dark:text-gray-300">
              Tienes cuenta?{" "}
                <a
                  href="/login"
                  className="ml-1 font-medium text-cyan-600 hover:underline dark:text-cyan-500"
                >
                   inicia sesión ahora!
                </a>{" "}
              </p>
            </div>
          </div>
        </div>
      </section>
    </>
  );
}

export default RegisterView;
