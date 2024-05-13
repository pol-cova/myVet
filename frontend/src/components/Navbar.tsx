
import { Button, Navbar, NavbarBrand, NavbarCollapse, NavbarLink, NavbarToggle } from "flowbite-react";


export default function NavMenu() {
    return (
        <Navbar fluid rounded>
            <NavbarBrand href="/">
            <img src="./src/assets/bxs-dog.svg" className="mr-3 h-6 sm:h-9" alt="myVet Logo"/>
            <span className="self-center whitespace-nowrap text-xl font-semibold dark:text-white">MyVet</span>
            </NavbarBrand>
            <div className="flex md:order-2">
                <Button href="/login" style={{backgroundColor:"#386641"}}>Login</Button>
                <NavbarToggle />
            </div>
            <NavbarCollapse>
                <NavbarLink href="/">
                    Home
                </NavbarLink>
                <NavbarLink href="/about">Sobre Nosotros</NavbarLink>
                <NavbarLink href="/testimonials">Testimonios</NavbarLink>
                <NavbarLink href="/services">Services</NavbarLink>
                <NavbarLink href="/contact">Contacto</NavbarLink>
                <NavbarLink href="/home">Dashboard</NavbarLink>
            </NavbarCollapse>
        </Navbar>
    );
}
