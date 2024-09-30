// src/components/PropertyList.js
import React, { useState, useEffect } from 'react';
import axiosInstance from '../utils/axiosConfig';

const PropertyList = ({ properties }) => {
  // Fetch properties when the component mounts
  useEffect(() => {
    const fetchProperties = async () => {
      try {
        const response = await axiosInstance.get('/properties');
        setProperties(response.data);
      } catch (error) {
        console.error('Error fetching properties:', error);
      }
    };

    fetchProperties();
  }, []);

  return (
    <div>
      <h2>Property Listings</h2>
      <ul>
        {properties.map((property) => (
          <li key={property.id}>
            <h3>{property.name}</h3>
            <p>Location: {property.location}</p>
            <p>Price: ${property.price}</p>
            <button>View Details</button>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default PropertyList;
