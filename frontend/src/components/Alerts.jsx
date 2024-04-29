import React from 'react';
import { HiInformationCircle } from "react-icons/hi";
import { Alert } from "flowbite-react";

// eslint-disable-next-line react/prop-types
function ErrorAlert({ message }) {
    return (
            <Alert color="failure" icon={HiInformationCircle}>

                <span className="font-medium">Error!</span> {message} .
            </Alert>
  );
}

export default ErrorAlert;