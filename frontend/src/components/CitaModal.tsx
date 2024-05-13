import { useState, useEffect } from "react";
import {
  Button,
  Checkbox,
  Label,
  Modal,
  TextInput,
  Select,
} from "flowbite-react";
// icons
import { MdPets } from "react-icons/md";

// axios
import axios from "axios";

export default function CitaModal({
  openModal,
  onCloseModal,
  fetchCitaCount,
}: {
  openModal: boolean;
  onCloseModal: () => void;
  fetchCitaCount: () => void;
}) {
  // cita modal data
  const [citaDate, setCitaDate] = useState("");
  const [citaTime, setCitaTime] = useState("");
  const [citaPetName, setCitaPetName] = useState("");
  const [service, setCitaPetService] = useState("");
  const [citaMail, setCitaMail] = useState("");
  const [citaPhone, setCitaPhone] = useState("");
  const [citaOwner, setCitaOwner] = useState("");

  // get avail hours
  const [hours, setHours] = useState([]);

  const fetchHours = async (date: string) => {
    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/appointment/hours",
        { date }
      );
      setHours(response.data.hours);
    } catch (error) {
      console.error(error);
    }
  };

  const handleDateChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const date = event.target.value;
    setCitaDate(date);
    fetchHours(date); // Fetch available hours for the selected date
  };

  // handleSubmit
  const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();

    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/appointment/create",
        {
          date: citaDate,
          hour: citaTime,
          petName: citaPetName,
          service: service,
          email: citaMail,
          phone: citaPhone,
          ownerName: citaOwner,
        }
      );
        console.log(response.data);
      // Clear the form
      setCitaDate("");
      setCitaTime("");
      setCitaPetName("");
      setCitaPetService("");
      setCitaMail("");
      setCitaPhone("");
      setCitaOwner("");
      onCloseModal();
      fetchCitaCount();
      alert("Cita registrada con éxito");
    } catch (error) {
      console.error(error);
      // Handle the error as needed
      alert("Error al registrar la cita");
    }
  };

  return (
    <>
      <Modal show={openModal} size="md" onClose={onCloseModal} popup>
        <Modal.Header />
        <Modal.Body>
          <form onSubmit={handleSubmit}>
            <div className="space-y-6">
              <h3 className="text-xl font-medium text-gray-900 dark:text-white">
                Registrar una cita!{" "}
              </h3>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="petName" value="Nombre de tu mascota: " />
                </div>
                <TextInput
                  rightIcon={MdPets}
                  id="petName"
                  placeholder="Max"
                  value={citaPetName}
                  onChange={(event) => setCitaPetName(event.target.value)}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="ownerName" value="Nombre del dueño: " />
                </div>
                <TextInput
                  id="ownerName"
                  placeholder="John Doe"
                  value={citaOwner}
                  onChange={(event) => setCitaOwner(event.target.value)}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="email" value="Correo electronico: " />
                </div>
                <TextInput
                  id="email"
                  type="email"
                  placeholder="example@example.com"
                  value={citaMail}
                  onChange={(event) => setCitaMail(event.target.value)}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="phone" value="Celular: " />
                </div>
                <TextInput
                  id="phone"
                  placeholder="3751* * * * *"
                  value={citaPhone}
                  onChange={(event) => setCitaPhone(event.target.value)}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="service" value="Servicio: " />
                </div>
                <Select
                  id="service"
                  value={service}
                  onChange={(event) => setCitaPetService(event.target.value)}
                  required
                >
                  <option value="">Selecciona una opción</option>
                  <option value="consulta">Consulta</option>
                  <option value="vacunacion">Vacunación</option>
                  <option value="cirugia">Cirugía</option>
                  <option value="peluqueria">Peluquería</option>
                </Select>
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="appointmentDate" value="Fecha de la cita: " />
                </div>
                <TextInput
                  type="date"
                  id="appointmentDate"
                  value={citaDate}
                  onChange={handleDateChange}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="appointmentHour" value="Hora de la cita: " />
                </div>
                <Select
                  id="appointmentHour"
                  value={citaTime}
                  onChange={(event) => setCitaTime(event.target.value)}
                  required
                >
                  <option value="">Selecciona una opción</option>
                  {hours
                    .sort((a, b) => {
                      const dateA = new Date(`1970/01/01 ${a}`);
                      const dateB = new Date(`1970/01/01 ${b}`);
                      return dateA.getTime() - dateB.getTime();
                    })
                    .map((hour, index) => (
                      <option key={index} value={hour}>
                        {hour}
                      </option>
                    ))}
                </Select>
              </div>
              <div className="flex justify-between">
                <div className="flex items-center gap-2">
                  <Checkbox id="remember" />
                  <Label htmlFor="remember">
                    Mantenerme informado sobre mi cita
                  </Label>
                </div>
              </div>
              <div className="w-full">
                <Button type="submit">Registrar cita</Button>
              </div>
            </div>
          </form>
        </Modal.Body>
      </Modal>
    </>
  );
}
