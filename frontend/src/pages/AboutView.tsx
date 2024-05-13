import NavMenu from "../components/Navbar";
function AboutView(){
    return(
        <>
        <NavMenu />
        <section className="bg-white dark:bg-gray-900">
  <div className="py-8 px-4 mx-auto max-w-screen-xl text-center lg:py-16 lg:px-6">
      <div className="mx-auto mb-8 max-w-screen-sm lg:mb-16">
          <h2 className="mb-4 text-4xl tracking-tight font-extrabold text-gray-900 dark:text-white">Nuestro Equipo</h2>
          <p className="font-light text-gray-500 sm:text-xl dark:text-gray-400">En MyVet todos somos una familia!</p>
      </div> 
      <div className="grid gap-8 lg:gap-16 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4">
          <div className="text-center text-gray-500 dark:text-gray-400">
              <img className="mx-auto mb-4 w-36 h-36 rounded-full" src="./src/assets/doc-1.jpeg" alt="Bonnie Avatar" />
              <h3 className="mb-1 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
                  <a href="#">Dr. Juan</a>
              </h3>
              <p>Veterinario Principal</p>
          </div>
          <div className="text-center text-gray-500 dark:text-gray-400">
              <img className="mx-auto mb-4 w-36 h-36 rounded-full" src="./src/assets/aux-1.jpeg" alt="Helene Avatar" />
              <h3 className="mb-1 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
                  <a href="#">Ana</a>
              </h3>
              <p>Auxiliar de Veterinario</p>
          </div>
          <div className="text-center text-gray-500 dark:text-gray-400">
              <img className="mx-auto mb-4 w-36 h-36 rounded-full" src="./src/assets/pel-1.jpeg" alt="Jese Avatar" />
              <h3 className="mb-1 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
                  <a href="#">Pepe</a>
              </h3>
              <p>Peluquero</p>
          </div>
          <div className="text-center text-gray-500 dark:text-gray-400">
              <img className="mx-auto mb-4 w-36 h-36 rounded-full" src="./src/assets/doc-4.jpeg" alt="Joseph Avatar" />
              <h3 className="mb-1 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
                  <a href="#">Dr. John</a>
              </h3>
              <p>Veterinario Especialista</p>
          </div>
    
      </div>  
  </div>
</section>
        </>
    )
}

export default AboutView;