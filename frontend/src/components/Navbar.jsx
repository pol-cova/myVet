import {
  Button,
  Navbar,
  NavbarBrand,
  NavbarCollapse,
  NavbarLink,
  NavbarToggle,
} from "flowbite-react";
import React from "react";

export function NavBar() {
  return (
    <Navbar fluid rounded>
      <NavbarBrand href="/">
        <img
          src="src/assets/bxs-dog.svg"
          className="mr-3 h-6 sm:h-9"
          alt="Pet icon"
        />
        <span
          className="self-center whitespace-nowrap text-xl font-semibold dark:text-white"
          style={{ color: "#386641" }}
        >
          MyVet System
        </span>
      </NavbarBrand>
      <div className="flex md:order-2">
        <Button style={{ backgroundColor: "#386641" }}>Iniciar Sesión</Button>
        <NavbarToggle />
      </div>
      <NavbarCollapse>
        <NavbarLink href="/">Home</NavbarLink>
        <NavbarLink href="#">Sobre Nosotros</NavbarLink>
        <NavbarLink href="#">Servicios</NavbarLink>
        <NavbarLink href="#">Equipo</NavbarLink>
        <NavbarLink href="#">Contacto</NavbarLink>
      </NavbarCollapse>
    </Navbar>
  );
}
