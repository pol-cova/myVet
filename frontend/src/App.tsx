import { useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'
import { Button } from 'flowbite-react';
import NavMenu from './components/Navbar'
import { HiCalendar } from 'react-icons/hi';


// import app pages
import LoginView from "./pages/LoginView.tsx";
import HomeView from "./pages/HomeView.tsx";
import RegisterView from './pages/RegisterView.tsx';
import AboutView from './pages/AboutView.tsx';
import ContactView from './pages/ContactView.tsx';
import TestimonialView from './pages/Testimonials.tsx';
import ServiceView from './pages/ServicesView.tsx';

// import modal
import CitaModalHome from './components/CitaModalHome.tsx';

function RedirectToHome() {
    const navigate = useNavigate();
    

    useEffect(() => {
        const token = localStorage.getItem('token');
        if (token) {
            navigate('/home');
        } else{
            navigate('/login')
        }
    }, [navigate]);

    return null;
}

function App() {
    const [openModalCita, setOpenModalCita] = useState(false);

    const onCloseCitaModal = () => {
        setOpenModalCita(false);
    };
    
    return (
        <Router>
            <Routes>
                <Route path="/login" element={<LoginView />} />
                <Route path="/home" element={<HomeView />} />
                <Route path="/register" element={<RegisterView />} />
                <Route path='/about' element={<AboutView />}/>
                <Route path='/contact' element={<ContactView />}/>
                <Route path='/services' element={<ServiceView />}/>
                <Route path='/testimonials' element={<TestimonialView />}/>
                <Route path="/" element={
                    <>
                    <NavMenu />
                    <CitaModalHome
        openModal={openModalCita}
        onCloseModal={onCloseCitaModal}
      />
                    <section className="bg-white dark:bg-gray-900">
    <div className="grid max-w-screen-xl px-4 py-8 mx-auto lg:gap-8 xl:gap-0 lg:py-16 lg:grid-cols-12">
        <div className="mr-auto place-self-center lg:col-span-7">
            <h1 className="max-w-2xl mb-4 text-4xl font-extrabold tracking-tight leading-none md:text-5xl xl:text-6xl dark:text-white">Cuidar de tu mascota nunca fue tan facil</h1>
            <p className="max-w-2xl mb-6 font-light text-gray-500 lg:mb-8 md:text-lg lg:text-xl dark:text-gray-400">Agenda una cita ahora para el mejor cuidado de tu mascota.</p>
            <Button color="success" onClick={() => setOpenModalCita(true)} className="py-2 px-4 text-lg">
                  <HiCalendar className="mr-3 h-6 w-6" />
                  Agendar cita
            </Button>
        </div>
        <div className="lg:mt-0 lg:col-span-5 lg:flex">
    <img src="./src/assets/dog.svg" alt="mockup" />
</div>          
    </div>
</section>
                    </>
                } />
            </Routes>
        </Router>
    )
}

export default App