import React, { useState, useEffect } from "react";
import axios from "axios";
import {
  Modal,
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeadCell,
  TableRow,
} from "flowbite-react";

export default function PetInfoModal({
  openModal,
  onCloseModal,
  petId,
}: {
  openModal: boolean;
  onCloseModal: () => void;
  petId: any;
}) {
  // fetch petTrat with petID -> int
  const [petTrat, setPetTrat] = useState([]);

  // fetch when open modal
  useEffect(() => {
    fetchPetTrat(petId);
  }, [openModal]);

  const fetchPetTrat = async (petID: any) => {
    try {
      const response = await axios.post(
        "http://127.0.0.1:18080/tratamiento/pet",
        {
          petID: petID,
        }
      );
      // Handle the response data as needed
      setPetTrat(response.data.tratamientos);
      console.log(response.data);
    } catch (error) {
      console.error("Failed to fetch pet trat:", error);
    }
  };
  return (
    <Modal show={openModal} size="md" onClose={onCloseModal} popup>
      <Modal.Header />
      <Modal.Body>
        <div>
          <div className="flex bg-blue-500 text-white p-3 rounded-t">
            <div id="trat" className="w-1/3">
              Tratamiento
            </div>
            <div className="w-1/3">Fecha</div>
            <div className="w-1/3">Costo</div>
          </div>
          {petTrat.map((trat, index) => (
            <div
              key={index}
              className="flex bg-white dark:border-gray-700 dark:bg-gray-800 p-3 border-b border-gray-200"
            >
              <div className="w-1/3 whitespace-nowrap font-medium text-gray-900 dark:text-white">
                {trat.tratamiento}
              </div>
              <div
                className="w-1/3"
                style={{ color: "black", fontSize: "16px" }}
              >
                {trat.date}
              </div>
              <div
                className="w-1/3"
                style={{ color: "black", fontSize: "16px" }}
              >
                ${trat.cost}
              </div>
            </div>
          ))}
        </div>
      </Modal.Body>
    </Modal>
  );
}
