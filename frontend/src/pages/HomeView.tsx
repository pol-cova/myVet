import { useEffect, useState } from 'react';
import {jwtDecode} from 'jwt-decode';
import { useNavigate } from 'react-router-dom';

// Dashboard components
import UserDashboard from '../components/UserDashboard';
import AdminDashboard from '../components/AdminDashboard';

function HomeView() {
    const navigate = useNavigate();
    const [user, setUser] = useState<any>(null);
    const token = localStorage.getItem('token');

    useEffect(() => {
        if (token) {
            const decodedUser = jwtDecode(token);
            setUser(decodedUser);
        } else {
            navigate('/login');
        }
    }, [token, navigate]);

    if (user && user.role === 'admin') {
        return (
            <>
            {user && <AdminDashboard user={user}/>}
            </>
        );
    }

    return (
        <>
        {user && <UserDashboard user={user}/>}       
        </>
    );
}
export default HomeView;