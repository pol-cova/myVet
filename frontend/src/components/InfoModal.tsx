import { useState } from "react";
import { Button, Checkbox, Label, Modal, TextInput, Select, Textarea } from "flowbite-react";
// icons 
import { MdPets} from "react-icons/md";
import { FaMoneyBillWave } from "react-icons/fa";


// axios
import axios from "axios";

export default function UpdatePet({openModal, onCloseModal, petId, fetchPets}: { openModal: boolean; onCloseModal: () => void; petId: any;  fetchPets: () => void}){

      // modal data
      const [weight, setWeight] = useState(0);
      const [height, setHeight] = useState(0);
    // handleSubmit
    const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
        event.preventDefault();


        try {
            const response = await axios.post('http://127.0.0.1:18080/pet/update', {
                petID: petId,
                weight: weight,
                height: height,
                // log data that are being sent

            });
            console.log(response.data);
            // Clear the form
            setWeight(0);
            setHeight(0);
            // Close the modal
            onCloseModal();
            // Fetch the updated pets
            fetchPets();
            alert("Mascota actualizada exitosamente.");
        } catch (error) {
            console.error(error);
            // Handle the error as needed
            alert("Error al registrar la mascota, intente de nuevo.");
        }
    };

    return(
        <>
        <Modal show={openModal} size="md" onClose={onCloseModal} popup>
        <Modal.Header />
        <Modal.Body>
        <form onSubmit={handleSubmit}>
          <div className="space-y-6">
            <h3 className="text-xl font-medium text-gray-900 dark:text-white">Actualizar mascota </h3>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="height" value="Altura de tu mascota (cm): " />
              </div>
              <TextInput
                id="height"
                placeholder="163"
                value={height}
                onChange={(event) => setHeight(parseFloat(event.target.value))}
                required
              />
            </div>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="weight" value="Peso de tu mascota: " />
              </div>
              <TextInput
                id="weight"
                placeholder="1"
                value={weight}
                onChange={(event) => setWeight(parseFloat(event.target.value))}
                rightIcon={MdPets}
                required
              />
            </div>
            <div className="w-full">
              <Button type="submit">Actualizar mascota</Button>
            </div>
          </div>
          </form>
        </Modal.Body>
      </Modal>
        </>
    );
}