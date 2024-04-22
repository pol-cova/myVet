// Router 
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom'

// Custom components
import { NavBar } from './components/Navbar'
import { Foot } from './components/Foot'

// Pages 
import Home from './pages/Home'

function App() {

  return (
    <>
      <Router>
        <NavBar />
        <Routes>
          <Route path="/" element={<Home />} />
        </Routes>
        <Foot />
      </Router>
    </>
  )
}

export default App
