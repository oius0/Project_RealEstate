// src/components/Search.js
import React, { useState } from 'react';
import axiosInstance from '../utils/axiosConfig';

const Search = ({ setProperties }) => {
  const [query, setQuery] = useState('');

  const handleInputChange = (e) => {
    setQuery(e.target.value);
  };

  const handleSearch = async (e) => {
    e.preventDefault();
    try {
      const response = await axiosInstance.get(`/properties?search=${query}`);
      setProperties(response.data);
    } catch (error) {
      console.error('Error fetching search results:', error);
    }
  };

  return (
    <form onSubmit={handleSearch}>
      <input
        type="text"
        placeholder="Search properties..."
        value={query}
        onChange={handleInputChange}
      />
      <button type="submit">Search</button>
    </form>
  );
};

export default Search;
