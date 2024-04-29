import React, { useState, useEffect } from "react";
import { CalendarIcon } from "@radix-ui/react-icons";
import TodayDate from "../utils/Date";
import ErrorAlert from "../components/Alerts.jsx";

function Home() {
  const [availableHours, setAvailableHours] = useState([]);
  const [formData, setFormData] = useState({
    petName: "",
    email: "",
    phone: "",
    date: "",
    hour: "",
    ownerName: "",
    service: "",
  });

  useEffect(() => {
    fetch('http://0.0.0.0:18080/api/appointment/hours')
        .then(response => response.json())
        .then(data => {
          if (Array.isArray(data.hours)) {
            setAvailableHours(data.hours);
          } else {
            console.error('Invalid data structure for available hours:', data);
          }
        })
        .catch(error => {
          console.error('Error fetching available hours:', error);
          setAvailableHours(["No hay horas disponibles"]);
        });
  }, []);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevData) => ({
      ...prevData,
      [name]: value,
    }));
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    console.log(formData);

    fetch("http://0.0.0.0:18080/api/appointment/create", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      mode: "no-cors", // Set the mode to 'no-cors'
      body: JSON.stringify(formData)
    })
        .then(response => {
          console.log(response);
        })
        .then(data => {
          console.log(data);
          alert("Cita agendada con éxito");
        })
        .catch(error => {
          console.error("Error:", error);
          alert("Error al agendar la cita");
        })
        .finally(() => {
          setFormData({
            petName: "",
            email: "",
            phone: "",
            date: "",
            hour: "",
            ownerName: "",
            service: "",
          });
        });
  };




  return (
      <section className="bg-white dark:bg-gray-900">
        <div className="grid max-w-screen-xl px-4 py-8 mx-auto lg:gap-8 xl:gap-0 lg:py-16 lg:grid-cols-12">
          <div className="mr-auto place-self-center lg:col-span-7">
            <h1 className="max-w-2xl mb-4 text-4xl font-extrabold tracking-tight leading-none md:text-5xl xl:text-6xl dark:text-white" style={{ color: "#386641" }}>
              Descubre una nueva forma de cuidar a tus mascotas con nosotros
            </h1>
            <p className="max-w-2xl mb-6 font-light text-gray-500 lg:mb-8 md:text-lg lg:text-xl dark:text-gray-400">
              Agenda una cita ahora, para que tu mascota reciba la mejor atención.
            </p>
            <div className="flex flex-col ">
              <form onSubmit={handleSubmit}>
                <div className="relative">
                  <input
                      type="text"
                      name="petName"
                      placeholder="Nombre de la mascota"
                      className="w-full border border-gray-300 rounded-lg p-3 mb-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                      value={formData.petName}
                      onChange={handleChange}
                      required
                  />
                </div>
                <div className="relative">
                  <input
                      type="text"
                      name="petName"
                      placeholder="Nombre de la dueñ@"
                      className="w-full border border-gray-300 rounded-lg p-3 mb-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                      value={formData.ownerName}
                      onChange={handleChange}
                      required
                  />
                </div>
                <div className="relative">
                  <input
                      type="email"
                      name="email"
                      placeholder="Email"
                      className="w-full border border-gray-300 rounded-lg p-3 mb-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                      value={formData.email}
                      onChange={handleChange}
                      required
                  />
                </div>
                <div className="relative">
                  <input
                      type="text"
                      name="phone"
                      placeholder="Celular"
                      className="w-full border border-gray-300 rounded-lg p-3 mb-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                      value={formData.phone}
                      onChange={handleChange}
                      required
                  />
                </div>
                <div className="relative">
                  <select
                      name="service"
                      className="w-full border border-gray-300 rounded-lg p-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                      value={formData.service}
                      onChange={handleChange}
                      required
                  >
                    <option value="">Servicio</option>
                    <option value="Consulta">Consulta</option>
                    <option value="Vacunación">Vacunación</option>
                    <option value="Desparasitación">Desparasitación</option>
                    <option value="Cirugía">Cirugía</option>
                    <option value="Peluquería">Peluquería</option>
                    <option value="Emergencia">Emergencia</option>
                  </select>
                </div>
                <label className="block mb-2 font-medium text-gray-700 dark:text-gray-300">Fecha y hora de la cita</label>
                <div className="flex items-center mb-3 space-x-4">
                  <div className="flex-1">
                    <input
                        name="date"
                        type="date"
                        placeholder="Fecha de la Cita"
                        className="w-full border border-gray-300 rounded-lg p-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                        value={formData.date}
                        onChange={handleChange}
                        min={TodayDate()} // Set the min attribute to the current date
                        required
                    />
                  </div>
                  <div className="flex-1">
                    <select
                        name="hour"
                        className="w-full border border-gray-300 rounded-lg p-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                        value={formData.hour}
                        onChange={handleChange}
                        required
                    >
                      <option value="">Horas</option>
                      {Array.isArray(availableHours) &&
                          availableHours.map((hour) => (
                              <option key={hour} value={hour}>
                                {hour}
                              </option>
                          ))}
                    </select>
                  </div>
                </div>
                <button
                    type="submit"
                    className="bg-blue-600 text-white rounded-lg px-4 py-2 hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-600 focus:ring-opacity-50"
                    style={{ backgroundColor: "#386641" }}
                >
                  <CalendarIcon className="inline-block w-5 h-6 mr-2" /> Agendar cita
                </button>
              </form>
            </div>
          </div>
          <div className="hidden lg:mt-0 lg:col-span-5 lg:flex">
            <img src="src/assets/2_dog.svg" alt="pet" />
          </div>
        </div>
      </section>
  );
}

export default Home;
