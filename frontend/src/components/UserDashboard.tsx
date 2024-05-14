import UserNav from "./UserNavbar";
import { useState, useEffect } from "react";
import { Button, ButtonGroup, Card, Badge } from "flowbite-react";
import { HiCalendar } from "react-icons/hi";
import { MdPets, MdDeleteForever } from "react-icons/md";

import axios from "axios";

// Modals
import PetModal from "./PetModal";
import CitaModal from "./CitaModal";
import DelPetModal from "./DelPetModal";
import PetInfoModal from "./PetInfoModal";

// imgs
import perroImg from "../assets/perro-1.jpg";
import gatoImg from "../assets/gato-1.png";
import exoticoImg from "../assets/exo-2.jpg";

export default function UserDashboard({ user }: { user: any }) {
  const [petCount, setPetCount] = useState(0);
  const [citaCount, setcitaCount] = useState(0);
  const [pets, setPets] = useState([]);
  // modal settings
  const [openModalCita, setOpenModalCita] = useState(false);
  const [openModalPet, setOpenModalPet] = useState(false);
  const [openModalDelPet, setOpenModalDelPet] = useState(false);
  const [oepnModalInfo, setOpenModalInfo] = useState(false);


  // OnClose PetModal
  const onCloseModalPet = () => {
    setOpenModalPet(false);
  };

  // OnClose CitaModal
  const onCloseCitaModal = () => {
    setOpenModalCita(false);
  };

  // OnClose DelPetModal
  const onCloseDelPetModal = () => {
    setOpenModalDelPet(false);
  };

  // OnClose ModalInfo
  const onCloseModalInfo = () =>{
    setOpenModalInfo(false);
  }

  const fetchPetCount = async () => {
    try {
      const response = await axios.post("http://127.0.0.1:18080/pet/count", {
        userID: user.userID,
      });
      setPetCount(response.data.count);
    } catch (error) {
      console.error("Failed to fetch pet count:", error);
    }
  };

  const fetchCitaCount = async () => {
    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/appointment/count",
        { mail: user.mail }
      );
      setcitaCount(response.data.count);
    } catch (error) {
      console.error("Failed to fetch cita count:", error);
    }
  };

  const fetchPets = async () => {
    try {
      const response = await axios.post("http://127.0.0.1:18080/pet/get", {
        userID: user.userID,
      });
      // Handle the response data as needed
      setPets(response.data.pets);
      console.log(response.data);
    } catch (error) {
      console.error("Failed to fetch pets:", error);
    }
  };




  const getImageSrc = (type: string) => {
    switch (type) {
      case "perro":
        return perroImg;
      case "gato":
        return gatoImg;
      case "exotico":
        return exoticoImg;
      default:
        return "";
    }
  };

  useEffect(() => {
    fetchPetCount();
    fetchCitaCount();
    fetchPets();
  }, [user.userID, user.mail]);
  return (
    <div className="antialiased bg-gray-50 dark:bg-gray-900">
      <PetModal
        openModal={openModalPet}
        onCloseModal={onCloseModalPet}
        user={user}
        fetchPetCount={fetchPetCount}
        fetchPets={fetchPets}
      />
      <CitaModal
        openModal={openModalCita}
        onCloseModal={onCloseCitaModal}
        fetchCitaCount={fetchCitaCount}
      />
      <DelPetModal
        openModal={openModalDelPet}
        onCloseModal={onCloseDelPetModal}
        petArray={pets}
        fetchPetCount={fetchPetCount}
        fetchPets={fetchPets}/>
      <UserNav user={user} />
      <main className="p-4 h-auto pt-10">
        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-4 mb-4">
          <div className="border-2 border-dashed rounded-lg border-gray-300 dark:border-gray-600 h-32 md:h-20">
            <div className="flex justify-between items-center p-4">
              <div>
                <h2 className="text-lg font-semibold dark:text-white">
                  Mascotas
                </h2>
                <p className="text-sm dark:text-gray-300">Total de mascotas</p>
              </div>
              <div className="flex items-center justify-center w-12 h-12 bg-gray-200 dark:bg-gray-700 rounded-full">
                <span className="text-lg font-semibold dark:text-white">
                  {petCount}
                </span>
              </div>
            </div>
          </div>
          <div className="border-2 border-dashed rounded-lg border-gray-300 dark:border-gray-600 h-32 md:h-20">
            <div className="flex justify-between items-center p-4">
              <div>
                <h2 className="text-lg font-semibold dark:text-white">Citas</h2>
                <p className="text-sm dark:text-gray-300">
                  Total de citas este mes
                </p>
              </div>
              <div className="flex items-center justify-center w-12 h-12 bg-gray-200 dark:bg-gray-700 rounded-full">
                <span className="text-lg font-semibold dark:text-white">
                  {citaCount}
                </span>
              </div>
            </div>
          </div>
          <div className=" rounded-lg h-32 md:h-20">
            <div className="flex flex-wrap gap-2">
              <ButtonGroup>
                <Button color="gray" onClick={() => setOpenModalCita(true)} className="py-2 px-4 text-lg">
                  <HiCalendar className="mr-3 h-6 w-6" />
                  Agendar cita
                </Button>
                <Button color="gray" onClick={() => setOpenModalPet(true)} className="py-2 px-4 text-lg">
                  <MdPets className="mr-3 h-6 w-6" />
                  Agregar mascota
                </Button>
                <Button color="red" onClick={() => setOpenModalDelPet(true)} className="py-2 px-4 text-lg">
                  <MdDeleteForever className="mr-3 h-6 w-6" />
                  Eliminar mascota
                </Button>
              </ButtonGroup>
            </div>
          </div>
        </div>
        <div className="border-dashed rounded-lg border-gray-300 dark:border-gray-600 mb-4 flex flex-wrap">
          {petCount === 0 ? (
            <div className="flex items-center justify-center h-full">
              <p className="text-xl text-center">
                Aun no tienes mascotas registradas :(
              </p>
            </div>
          ) : (
            pets.map((pet, index) => (
              <Card key={index} className="max-w-xs rounded-lg m-2">
                <img
                  className="rounded-t-lg"
                  src={getImageSrc(pet.type)}
                  alt="pet"
                  style={{ height: "300px", objectFit: "cover" }}
                />
                <div className="flex items-center justify-between p-4 dark:bg-gray-800 rounded-lg shadow-md">
                  <div>
                    <h2 className="text-2xl font-bold dark:text-white">
                      {pet.name}
                    </h2>
                    <p className="text-sm text-gray-500 dark:text-gray-300">
                      Especie: {pet.type}
                    </p>
                    <Badge color="indigo" className="mt-2 text-center justify-center">
                      {pet.genre}
                    </Badge>
                  </div>
                  <div className="flex items-center justify-center w-12 h-12">
                    <span className="text-lg font-bold dark:text-white  text-center inline-block">
                      {pet.age} años
                    </span>
                  </div>
                </div>
                <PetInfoModal
                  openModal={oepnModalInfo}
                  onCloseModal={onCloseModalInfo}
                  petId={pet.petID}
                />
                <Button className="inline-flex w-full items-center justify-center rounded-lg bg-gray-800 px-4 py-2.5 text-white hover:bg-gray-700 focus:outline-none focus:ring-4 focus:ring-gray-300 dark:bg-gray-700 dark:hover:bg-gray-600 dark:focus:ring-gray-700 sm:w-auto"
                onClick={() => setOpenModalInfo(true)}>
                  Ver Tratamientos
                </Button>
              </Card>
            ))
          )}
        </div>
      </main>
    </div>
  );
}
