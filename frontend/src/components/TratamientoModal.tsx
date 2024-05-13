import { useState } from "react";
import { Button, Checkbox, Label, Modal, TextInput, Select, Textarea } from "flowbite-react";
// icons 
import { MdPets} from "react-icons/md";
import { FaMoneyBillWave } from "react-icons/fa";


// axios
import axios from "axios";

export default function TratamientoModal({openModal, onCloseModal, user, ownerId, fetchTratamientos, petId}: { openModal: boolean; onCloseModal: () => void; user: any; ownerId: any; fetchTratamientos: () => void; petId: any;}){

      // modal data
    const [cost, setCost] = useState(0);
    const [description, setDescription] = useState("");

    // handleSubmit
    const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
        event.preventDefault();

        // Get current date
        const currentDate = new Date();
        // Format date as yyyy-mm-dd
        const formattedDate = currentDate.toISOString().split('T')[0];

        try {
            const response = await axios.post('http://127.0.0.1:18080/tratamiento/create', {
                medID: user.userID,
                petID: petId,
                userID: ownerId,
                date: formattedDate,
                cost: cost,
                tratamiento: description
                // log data that are being sent

            });
            console.log(response.data);
            // Clear the form
            setCost(0);
            setDescription("");
            // Close the modal
            onCloseModal();
            fetchTratamientos();
            alert("Tratamiento registrado exitosamente.");
        } catch (error) {
            console.error(error);
            // Handle the error as needed
            alert("Error al registrar el tratamiento, intente de nuevo.");
        }
    };

    return(
        <>
        <Modal show={openModal} size="md" onClose={onCloseModal} popup>
        <Modal.Header />
        <Modal.Body>
        <form onSubmit={handleSubmit}>
          <div className="space-y-6">
            <h3 className="text-xl font-medium text-gray-900 dark:text-white">Nuevo tratamiento </h3>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="tratamiento" value="Descripcion del tratamiento: " />
              </div>
              <TextInput
                id="tramamiento"
                placeholder="Inyeccion..."
                value={description}
                onChange={(event) => setDescription(event.target.value)}
                required
              />
            </div>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="cost" value="Costo del tratamiento: " />
              </div>
              <TextInput
                id="cost"
                placeholder="1"
                value={cost}
                onChange={(event) => setCost(parseFloat(event.target.value))}
                rightIcon={FaMoneyBillWave}
                required
              />
            </div>
            <div className="w-full">
              <Button type="submit">Registrar mi tratamiento</Button>
            </div>
          </div>
          </form>
        </Modal.Body>
      </Modal>
        </>
    );
}