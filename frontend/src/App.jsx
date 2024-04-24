// Router 
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'

// Custom components
import { NavBar } from './components/Navbar'
import { Foot } from './components/Foot'

// Pages 
import Home from './pages/Home'
import Login from './pages/Login'
import Signup from './pages/Signup'

function App() {

  return (
    <>
      <Router>
        <NavBar />
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/login" element={<Login />} />
          <Route path="/signup" element={<Signup />} />
        </Routes>
        <Foot />
      </Router>
    </>
  )
}

export default App
