import React, { useState } from "react";
import { CalendarIcon } from "@radix-ui/react-icons";
import TodayDate from "../utils/Date";

function Home() {
  const [formData, setFormData] = useState({
    petName: "",
    email: "",
    phone: "",
    date: "",
    time: "",
  });

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prevData) => ({
      ...prevData,
      [name]: value,
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    console.log(formData);

    const { petName, email, phone, date, time } = formData;
    const url = `http://127.0.0.1:18080/api/new/visit/${petName}/${email}/${phone}/${date}/${time}`;

    try {
      const response = await fetch(url, {
        method: "POST",
      });
      const data = await response.json();
      console.log(data); // Handle response data if needed
      alert("Cita agendada con éxito");
      setFormData({
        petName: "",
        email: "",
        phone: "",
        date: "",
        time: "",
      });
    } catch (error) {
      console.error("Error:", error); // Handle error if needed
      alert("Error al agendar la cita");
      setFormData({
        petName: "",
        email: "",
        phone: "",
        date: "",
        time: "",
      });
    }
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
                    required
                  />
                </div>
                <div className="flex-1">
                  <select
                    name="time"
                    className="w-full border border-gray-300 rounded-lg p-3 focus:outline-none focus:ring-2 focus:ring-blue-600"
                    value={formData.time}
                    onChange={handleChange}
                    required
                  >
                    <option value=""> Horas</option>
                    <option value="09:00">09:00 AM</option>
                    <option value="10:00">10:00 AM</option>
                    <option value="11:00">11:00 AM</option>
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
