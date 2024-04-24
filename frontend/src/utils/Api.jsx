import { useState, useEffect } from "react";
const API_URL = "http://127.0.0.1:18080/";

export const helloApi = () => {
    const [data, setData] = useState(null);
    useEffect(() => {
        fetch(`${API_URL}api/hello`)
        .then((res) => res.json())
        .then((data) => setData(data));
    }, []);
    return data;
};

export const getAvailableHours = (date) => {
    const [data, setData] = useState(null);
    useEffect(() => {
        fetch(`${API_URL}api/get/available/hours/date=${date}`)
        .then((res) => res.json())
        .then((data) => setData(data));
    }, [date]);
    return data;
};

export const postAppointment = (petName, mail, phone, date, hour) => {
    const [data, setData] = useState(null);
    fetch(`${API_URL}api/new/visit/petName=${petName}&mail=${mail}&phone=${phone}&date=${date}&hour=${hour}`)
    .then((res) => res.json())
    .then((data) => setData(data));
    return data;
};