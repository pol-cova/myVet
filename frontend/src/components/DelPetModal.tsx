import { Button, Modal } from "flowbite-react";
import { useState } from "react";
import { HiOutlineExclamationCircle } from "react-icons/hi";
import axios from "axios";

export default function DelPetModal({openModal, onCloseModal, petArray, fetchPetCount, fetchPets}: { openModal: boolean, onCloseModal: () => void, petArray: any[]; fetchPetCount: () => void; fetchPets: () => void;}) {
    // handleSubmit
    const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
        event.preventDefault();
        const formData = new FormData(event.currentTarget);
        const petID = formData.get("pet");

        try {
            const response = await axios.post('http://127.0.0.1:18080/pet/delete', {
                petID: petID
            });
            console.log(response.data);
            onCloseModal();
            fetchPetCount();
            fetchPets();
            alert("Mascota eliminada con éxito");
        } catch (error) {
            console.error(error);
            // Handle the error as needed
            alert("Error al eliminar la mascota");
        }
    };
    return (
        <>
          <Modal show={openModal} size="md" onClose={onCloseModal} popup>
            <Modal.Header />
            <Modal.Body>
              <div className="text-center">
                <HiOutlineExclamationCircle className="mx-auto mb-4 h-14 w-14 text-gray-400 dark:text-gray-200" />
                <h3 className="mb-5 text-lg font-normal text-gray-500 dark:text-gray-400">
                  Selecciona una mascota a Eliminar:
                </h3>
                <form onSubmit={handleSubmit}>
                <div className="flex flex-col gap-2">
                  {petArray.map((pet, index) => (
                    <div key={index} className="flex items-center gap-2">
                      <input type="radio" id={pet.name} name="pet" value={pet.petID} />
                      <label htmlFor={pet.name}>{pet.name}</label>
                    </div>
                  ))}
                </div>
                <br></br>
                <div className="flex justify-center gap-4">
                  <Button color="failure" type="submit">
                    {"Si, eliminar."}
                  </Button>
                  <Button color="gray" onClick={onCloseModal}>
                    No, cerrar
                  </Button>
                </div>  
                </form>
              </div>
            </Modal.Body>
          </Modal>
        </>
      );
}