import NavMenu from "../components/Navbar";

import { BiHealth } from "react-icons/bi";
import { IoMdCut } from "react-icons/io";
import { MdOutlinePets } from "react-icons/md";
import { FaNotesMedical } from "react-icons/fa";
import { FaHouseChimneyMedical } from "react-icons/fa6";
import { TbVaccine } from "react-icons/tb";


function ServicesView(){
    return(
        <>
        <NavMenu />
        <section className="bg-white dark:bg-gray-900">
  <div className="py-8 px-4 mx-auto max-w-screen-xl sm:py-16 lg:px-6">
      <div className="max-w-screen-md mb-8 lg:mb-16">
          <h2 className="mb-4 text-4xl tracking-tight font-extrabold text-gray-900 dark:text-white">Diseñado para satisfacer las necesidades de tu mascota.</h2>
          <p className="text-gray-500 sm:text-xl dark:text-gray-400">Aqui en MyVet nos precupamos por tu mascota, por ello diseñamos soluciones para matenerla siempre al cuidado.</p>
      </div>
      <div className="space-y-8 md:grid md:grid-cols-2 lg:grid-cols-3 md:gap-12 md:space-y-0">
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <FaHouseChimneyMedical className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
                </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Pensión</h3>
              <p className="text-gray-500 dark:text-gray-400">Vaz de viaje a un viaje corto esta es la perfecta opcion para ti, contamos con comodas instalaciones para maneter al cuidado a tu mascota durante tu viaje.</p>
          </div>
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <MdOutlinePets className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
              </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Accesorios</h3>
              <p className="text-gray-500 dark:text-gray-400">Encuentra todo lo que necesita tu mascota a muy poco precio.</p>
          </div>
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <IoMdCut className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
              </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Estetica</h3>
              <p className="text-gray-500 dark:text-gray-400">Contamos con un excelente servicio de estetica para mascotas para dejar increible a tu pequeño.</p>
          </div>
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <TbVaccine className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
              </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Vacunas</h3>
              <p className="text-gray-500 dark:text-gray-400">Con nosotros lleva al corriente todas las vacunas de tus mascotas.</p>
          </div>
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <BiHealth className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
              </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Emergencias</h3>
              <p className="text-gray-500 dark:text-gray-400">Contamos con un excelente servicio de emergencias las 24 horas los 365 dias del año.</p>
          </div>
          <div>
              <div className="flex justify-center items-center mb-4 w-10 h-10 rounded-full bg-primary-100 lg:h-12 lg:w-12 dark:bg-primary-900">
                <FaNotesMedical className="w-5 h-5 text-primary-600 lg:w-6 lg:h-6 dark:text-primary-300"/>
              </div>
              <h3 className="mb-2 text-xl font-bold dark:text-white">Chequeos</h3>
              <p className="text-gray-500 dark:text-gray-400">Contamos con los mejores especialistas para el cuidado de tu mascota.</p>
          </div>
      </div>
  </div>
</section>
        </>
    )
}
export default ServicesView;