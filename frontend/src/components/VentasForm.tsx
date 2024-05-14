import {
    Button,
    Label,
    TextInput,
} from "flowbite-react";
import { useState } from "react";
import axios from "axios";

/*
DB Scheme 

VentaID -> Integer
Monto -> Float
Concepto -> String
Date -> Today
Vendedor -> UserID

*/


export default function VentasForm({user, fetchVentas}:{user:any; fetchVentas: () => void}){

    const [concepto, setConcepto] = useState("");
    const [monto, setMonto] = useState(0);
    const [recibido, setRecibido] = useState(0);
    const [cambio, setCambio] = useState(0);

    const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
        event.preventDefault();
        setCambio(0);

        // Get current date
        const currentDate = new Date();
        // Format date as yyyy-mm-dd
        const formattedDate = currentDate.toISOString().split('T')[0];

        try {
            const response = await axios.post('http://127.0.0.1:18080/venta/create', {
                userID: user.userID,
                monto: monto,
                concepto: concepto,
                date: formattedDate,
                recibido: recibido,
                cambio: cambio

            });

            if(monto <= recibido){
              setCambio(recibido-monto);
            }
            console.log(cambio)

                            // log data that are being sent
                            console.log('Data types being sent:');
                            console.log('userID:', typeof user.userID);
                            console.log('monto:', typeof monto);
                            console.log('concepto:', typeof concepto);
                            console.log('date:', typeof formattedDate);
                            console.log('recibido:', typeof recibido);
                            console.log('cambio:', cambio);
            
            console.log(response.data);
            // Clear the form
            setRecibido(0);
            setMonto(0);
            setConcepto("");
            // Close the modal
            fetchVentas();
            alert(`Venta registrada con éxito. Cambio: ${cambio}`);
            setCambio(0);
        } catch (error) {
            console.error(error);
            // Handle the error as needed
            alert("Error al registrar la venta, intente de nuevo.");
        }
    };
    return (
        <>
        <form onSubmit={handleSubmit}>
        <div className="space-y-6">
              <h3 className="text-xl font-medium text-gray-900 dark:text-white">
                Registrar una Venta{" "}
              </h3>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="Concepto" value="Concepto de la venta: " />
                </div>
                <TextInput
                  id="Concepto"
                  placeholder="Venta de croquetas"
                  value={concepto}
                  onChange={(event) => setConcepto(event.target.value)}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="Monto" value="Monto de la venta($): " />
                </div>
                <TextInput
                  id="Monto"
                  type="number"
                  placeholder="150.00"
                  value={monto}
                  onChange={(event) => setMonto(parseFloat(event.target.value))}
                  required
                />
              </div>
              <div>
                <div className="mb-2 block">
                  <Label htmlFor="Recibido" value="Monto recibido($): " />
                </div>
                <TextInput
                  id="Recibido"
                  type="number"
                  placeholder="400"
                  value={recibido}
                  onChange={(event) => setRecibido(parseFloat(event.target.value))}
                  required
                />
              </div>
              <div className="w-full">
                <Button type="submit">Registrar venta</Button>
              </div>
            </div>
        </form>
        </>
    )
}