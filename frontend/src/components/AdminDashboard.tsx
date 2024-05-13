import AdminNav from "./AdminNavbar";
import { useState, useEffect } from "react";
import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeadCell,
  TableRow,
  Tabs,
  Button,
} from "flowbite-react";
import { MdPets, MdEdit } from "react-icons/md";
import {
  HiClipboardList,
  HiCalendar,
} from "react-icons/hi";
import { FaFileInvoiceDollar, FaFacebookMessenger, FaMedkit } from "react-icons/fa";

// import custom modal
import TratamientoModal from "./TratamientoModal";


import axios from "axios";

export default function AdminDashboard({ user }: { user: any }) {
  const [petCount, setPetCount] = useState(0);
  const [citaCount, setcitaCount] = useState(0);
  const [citaDoneCount, setcitaDoneCount] = useState(0);
  const [userCount, setUserCount] = useState(0);
  const [pets, setPets] = useState([]);
  const [citas, setCitas] = useState([]);
  const [tratamiento, setTratamientos] = useState([]);
  const [petOwner, setPetOwner] = useState({});

  const [openModal, setOpenModal] = useState(false);

  const onCloseModal = () => {
    setOpenModal(false);
  }



  // get users count
  const fetchUsersCount = async () => {
    try {
      const response = await axios.get("http://127.0.0.1:18080/users/all");
      setUserCount(response.data.count);
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  };

  // get pets
  const fetchPets = async () => {
    try {
      const response = await axios.get("http://127.0.0.1:18080/pet/all");
      setPetCount(response.data.count);
      setPets(response.data.pets);
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  };

  // get citas
  const fetchCitas = async () => {
    try {
      const response = await axios.get(
        "http://127.0.0.1:18080/appointment/all"
      );
      setcitaCount(response.data.count);
      setcitaDoneCount(response.data.done);
      setCitas(response.data.appointments);
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  };

  // complete cita
  const completeAppointment = async (appointmentID: number) => {
    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/appointment/complete",
        { appointmentID }
      );
      if (response.data.status === "success") {
        console.log(response.data.msg);
        // Refresh your data here
        fetchCitas();
      }
    } catch (error) {
      console.error("Error completing appointment:", error);
      alert("Error al completar la cita");
    }
  };


  // get all tratamientos
  const fetchTratamientos = async () => {
    try {
      const response = await axios.get("http://127.0.0.1:18080/tratamiento/all");
      setTratamientos(response.data.tratamientos);
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  };



  useEffect(() => {
    fetchUsersCount();
    fetchPets();
    fetchCitas();
    fetchTratamientos();
  }, []);
  return (
    <div className="antialiased bg-gray-50 dark:bg-gray-900">
      <AdminNav user={user} />
      <main className="p-4 h-auto pt-10">
        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-4 mb-4">
          <div className="border-2 border-dashed rounded-lg border-gray-300 dark:border-gray-600 h-32 md:h-20">
            <div className="flex justify-between items-center p-4">
              <div>
                <h2 className="text-lg font-semibold dark:text-white">
                  Mascotas
                </h2>
                <p className="text-sm dark:text-gray-300">
                  Total de mascotas en el sistema
                </p>
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
                <h2 className="text-lg font-semibold dark:text-white">
                  Citas Pendientes
                </h2>
                <p className="text-sm dark:text-gray-300">
                  Total de citas pendientes
                </p>
              </div>
              <div className="flex items-center justify-center w-12 h-12 bg-red-200 dark:bg-red-700 rounded-full">
                <span className="text-lg font-semibold dark:text-white">
                  {citaCount}
                </span>
              </div>
            </div>
          </div>
          <div className="border-2 border-dashed rounded-lg border-gray-300 dark:border-gray-600 h-32 md:h-20">
            <div className="flex justify-between items-center p-4">
              <div>
                <h2 className="text-lg font-semibold dark:text-white">
                  Citas Completadas
                </h2>
                <p className="text-sm dark:text-gray-300">
                  Total de citas completadas
                </p>
              </div>
              <div className="flex items-center justify-center w-12 h-12 bg-green-200 dark:bg-green-700 rounded-full">
                <span className="text-lg font-semibold dark:text-white">
                  {citaDoneCount}
                </span>
              </div>
            </div>
          </div>
          <div className="border-2 border-dashed rounded-lg border-gray-300 dark:border-gray-600 h-32 md:h-20">
            <div className="flex justify-between items-center p-4">
              <div>
                <h2 className="text-lg font-semibold dark:text-white">
                  Usuarios
                </h2>
                <p className="text-sm dark:text-gray-300">
                  Total de usuarios registrados
                </p>
              </div>
              <div className="flex items-center justify-center w-12 h-12 bg-gray-200 dark:bg-gray-700 rounded-full">
                <span className="text-lg font-semibold dark:text-white">
                  {userCount}
                </span>
              </div>
            </div>
          </div>
        </div>
        <Tabs aria-label="Tabs with underline" style="underline">
          <Tabs.Item active title="Citas" icon={HiCalendar}>
            <div className="border-dashed rounded-lg border-gray-300 dark:border-gray-600 mb-4 flex flex-wrap">
              <div className="overflow-x-auto w-full" id="citas-pendientes">
                <Table>
                  <TableHead>
                    <TableHeadCell>Dueño</TableHeadCell>
                    <TableHeadCell>Nombre Mascota</TableHeadCell>
                    <TableHeadCell>Servicio</TableHeadCell>
                    <TableHeadCell>Dia</TableHeadCell>
                    <TableHeadCell>Hora</TableHeadCell>
                    <TableHeadCell>Contacto</TableHeadCell>
                    <TableHeadCell>Estatus</TableHeadCell>
                    <TableHeadCell>
                      <span className="sr-only">Edit</span>
                    </TableHeadCell>
                  </TableHead>
                  <TableBody className="divide-y">
                    {citas.map((cita, index) => (
                      <TableRow
                        key={index}
                        className="bg-white dark:border-gray-700 dark:bg-gray-800"
                      >
                        <TableCell className="whitespace-nowrap font-medium text-gray-900 dark:text-white">
                          {cita.OwnerName}
                        </TableCell>
                        <TableCell>{cita.PetName}</TableCell>
                        <TableCell>{cita.Service}</TableCell>
                        <TableCell>{cita.AppointmentDate}</TableCell>
                        <TableCell>{cita.AppointmentTime}</TableCell>
                        <TableCell>{cita.Phone}</TableCell>
                        <TableCell>
                          {cita.Status === 0 ? (
                            <Button
                              onClick={() =>
                                completeAppointment(cita.AppointmentID)
                              }
                            >
                              Completar
                            </Button>
                          ) : (
                            <span role="img" aria-label="check">
                              ✅
                            </span>
                          )}
                        </TableCell>
                      </TableRow>
                    ))}
                  </TableBody>
                </Table>
              </div>
            </div>
          </Tabs.Item>
          <Tabs.Item title="Mascotas" icon={MdPets}>
            <div className="border-dashed rounded-lg border-gray-300 dark:border-gray-600 mb-4 flex flex-wrap">
              <div className="overflow-x-auto w-full" id="mascotas">
                <Table>
                  <TableHead>
                    <TableHeadCell>Nombre</TableHeadCell>
                    <TableHeadCell>Edad</TableHeadCell>
                    <TableHeadCell>Especie</TableHeadCell>
                    <TableHeadCell>Sexo</TableHeadCell>
                    <TableHeadCell>Dueño</TableHeadCell>
                    <TableHeadCell>Detalles</TableHeadCell>
                    <TableHeadCell>Tratar</TableHeadCell>
                    <TableHeadCell>
                      <span className="sr-only">Edit</span>
                    </TableHeadCell>
                  </TableHead>
                  <TableBody className="divide-y">
                    {pets.map((pet, index) => (
                      <TableRow
                        key={index}
                        className="bg-white dark:border-gray-700 dark:bg-gray-800"
                      >
                        <TableCell className="whitespace-nowrap font-medium text-gray-900 dark:text-white">
                          {pet.name}
                        </TableCell>
                        <TableCell>{pet.age}</TableCell>
                        <TableCell>{pet.type}</TableCell>
                        <TableCell>{pet.genre}</TableCell>
                        <TableCell>{pet.ownerName}</TableCell>
                        <TableCell>
                            <Button color="dark">
                                <MdEdit  className="mr-3 h-4 w-4" />
                                Editar
                            </Button>
                        </TableCell>
                        <TableCell>
                            <Button color="light" onClick={() => setOpenModal(true)} >
                                <FaMedkit className="mr-3 h-4 w-4" />
                                Tratar
                            </Button>
                        </TableCell>
                        <TratamientoModal openModal={openModal} onCloseModal={onCloseModal} user={user} petId={pet.petID} ownerId={pet.ownerID} fetchTratamientos={fetchTratamientos} />
                      </TableRow>
                    ))}
                  </TableBody>
                </Table>
              </div>
            </div>
          </Tabs.Item>
          <Tabs.Item title="Facturas" icon={FaFileInvoiceDollar}>
            This is{" "}
            <span className="font-medium text-gray-800 dark:text-white">
              Settings tab's associated content
            </span>
            . Clicking another tab will toggle the visibility of this one for
            the next. The tab JavaScript swaps classes to control the content
            visibility and styling.
          </Tabs.Item>
          <Tabs.Item title="Tratamientos" icon={HiClipboardList}>
            <div className="border-dashed rounded-lg border-gray-300 dark:border-gray-600 mb-4 flex flex-wrap">
              <div className="overflow-x-auto w-full" id="tratamientos">
                <Table>
                  <TableHead>
                    <TableHeadCell>Dueño</TableHeadCell>
                    <TableHeadCell>Mascota</TableHeadCell>
                    <TableHeadCell>Tratamiento</TableHeadCell>
                    <TableHeadCell>Costo</TableHeadCell>
                    <TableHeadCell>Fecha</TableHeadCell>
                  </TableHead>
                  <TableBody className="divide-y">
                    {tratamiento.map((trat, index) => (
                      <TableRow
                        key={index}
                        className="bg-white dark:border-gray-700 dark:bg-gray-800"
                      >
                        <TableCell className="whitespace-nowrap font-medium text-gray-900 dark:text-white">
                          {trat.OwnerName}
                        </TableCell>
                        <TableCell>{trat.PetName}</TableCell>
                        <TableCell>{trat.tratamiento}</TableCell>
                        <TableCell>{trat.cost}</TableCell>
                        <TableCell>{trat.date}</TableCell>
                      </TableRow>
                    ))}
                  </TableBody>
                </Table>
              </div>
            </div>
          </Tabs.Item>
          <Tabs.Item  title="Mensajes" icon={FaFacebookMessenger}>
            Disabled content
          </Tabs.Item>
        </Tabs>
      </main>
    </div>
  );
}
