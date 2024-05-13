import {
    Avatar,
    Dropdown,
    Navbar,
  } from "flowbite-react";

import { useNavigate } from "react-router-dom";

export default function UserNav({user} : {user: any}){
    const navigate = useNavigate();

    const handleLogout = () => {
        localStorage.removeItem('token');
        navigate('/login');
    }
    return (
        <>
         <Navbar fluid rounded>
      <Navbar.Brand href="/home">
        <img src="./src/assets/bxs-dog.svg" className="mr-3 h-6 sm:h-9" alt="Flowbite React Logo" />
        <span className="self-center whitespace-nowrap text-xl font-semibold dark:text-white">MyVet</span>
      </Navbar.Brand>
      <div className="flex md:order-2">
        <Dropdown
          arrowIcon={false}
          inline
          label={
            <Avatar alt="User settings" img="https://flowbite.com/docs/images/people/profile-picture-5.jpg" rounded />
          }
        >
          <Dropdown.Header>
            <span className="block text-sm">@{user?.username}</span>
          </Dropdown.Header>
          <Dropdown.Item>Perfil</Dropdown.Item>
          <Dropdown.Item>Configuracion</Dropdown.Item>
          <Dropdown.Item>Soporte</Dropdown.Item>
          <Dropdown.Divider />
          <Dropdown.Item onClick={handleLogout}>Salir</Dropdown.Item>
        </Dropdown>
        <Navbar.Toggle />
      </div>
      <Navbar.Collapse>
        <Navbar.Link href="#">Sobre Nosotros</Navbar.Link>
        <Navbar.Link href="#">Servicios</Navbar.Link>
        <Navbar.Link href="#">Precios</Navbar.Link>
        <Navbar.Link href="#">Contacto</Navbar.Link>
      </Navbar.Collapse>
    </Navbar>
        </>
    );
}