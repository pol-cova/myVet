import { useEffect } from 'react'
import { useNavigate } from 'react-router-dom';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'
import NavMenu from './components/Navbar'


// import app pages
import LoginView from "./pages/LoginView.tsx";
import HomeView from "./pages/HomeView.tsx";
import RegisterView from './pages/RegisterView.tsx';

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
    return (
        <Router>
            <Routes>
                <Route path="/login" element={<LoginView />} />
                <Route path="/home" element={<HomeView />} />
                <Route path="/register" element={<RegisterView />} />
                <Route path="/" element={
                    <>
                    <NavMenu />
                        <h1>INDEX</h1>
                    </>
                } />
            </Routes>
        </Router>
    )
}

export default App