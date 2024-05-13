import { useState } from "react";
import { Button, Checkbox, Label, Modal, TextInput, Select } from "flowbite-react";
// icons 
import { MdPets} from "react-icons/md";

// axios
import axios from "axios";

export default function PetModal({openModal, onCloseModal, user, fetchPetCount, fetchPets}: { openModal: boolean; onCloseModal: () => void; user: any; fetchPetCount: () => void; fetchPets: () => void;}){
      // pet modal data
    const [petName, setPetName] = useState("");
    const [petType, setPetType] = useState("");
    const [petGenre, setPetGenre] = useState("");
    const [petAge, setPetAge] = useState(0);

    // handleSubmit
    const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
        event.preventDefault();

        try {
            const response = await axios.post('http://127.0.0.1:18080/pet/add', {
                name: petName,
                type: petType,
                age: petAge,
                genre: petGenre,
                userID: user.userID
            });
            console.log(response.data);
            // Clear the form
            setPetName("");
            setPetType("");
            setPetAge(0);
            setPetGenre("");
            onCloseModal();
            fetchPetCount();
            fetchPets();
            alert("Mascota registrada con éxito");
        } catch (error) {
            console.error(error);
            // Handle the error as needed
            alert("Error al registrar la mascota");
        }
    };

    return(
        <>
        <Modal show={openModal} size="md" onClose={onCloseModal} popup>
        <Modal.Header />
        <Modal.Body>
        <form onSubmit={handleSubmit}>
          <div className="space-y-6">
            <h3 className="text-xl font-medium text-gray-900 dark:text-white">Registrar una nueva mascota! </h3>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="petName" value="Nombre de tu mascota: " />
              </div>
              <TextInput
              rightIcon={MdPets}
                id="petName"
                placeholder="Max"
                value={petName}
                onChange={(event) => setPetName(event.target.value)}
                required
              />
            </div>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="petAge" value="Edad de tu mascota (años): " />
              </div>
              <TextInput
                id="petAge"
                placeholder="1"
                value={petAge}
                onChange={(event) => setPetAge(parseInt(event.target.value))}
                required
              />
            </div>
            <div>
                <div className="mb-2 block">
                    <Label htmlFor="petType" value="Tipo de mascota: " />
                </div>
                <Select
                    id="petType"
                    value={petType}
                    onChange={(event) => setPetType(event.target.value)}
                    required
                >
                    <option value="">Selecciona una opción</option>
                    <option value="perro">Perro</option>
                    <option value="gato">Gato</option>
                    <option value="exotico">Exotica</option>
                </Select>
            </div>
            <div>
              <div className="mb-2 block">
                <Label htmlFor="genre" value="Sexo: " />
              </div>
              <Select
                id="genre"
                value={petGenre}
                onChange={(event) => setPetGenre(event.target.value)}
                required
              >
                <option value="">Selecciona una opción</option>
                <option value="macho">Macho</option>
                <option value="hembra">Hembra</option>
              </Select>
            </div>
            <div className="flex justify-between">
              <div className="flex items-center gap-2">
                <Checkbox id="remember" />
                <Label htmlFor="remember">Mantenerme informado sobre mi mascota</Label>
              </div>
            </div>
            <div className="w-full">
              <Button type="submit">Registrar mi mascota</Button>
            </div>
          </div>
          </form>
        </Modal.Body>
      </Modal>
        </>
    );
}