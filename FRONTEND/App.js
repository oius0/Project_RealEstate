// src/App.js
import React, { useState } from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import PropertyList from './components/PropertyList';
import Search from './components/Search';
import Login from './components/Login';

const App = () => {
  const [properties, setProperties] = useState([]);
  const [authToken, setAuthToken] = useState(localStorage.getItem('authToken') || '');

  return (
    <Router>
      <div>
        <h1>Real Estate Platform</h1>
        {!authToken ? (
          <Login setAuthToken={setAuthToken} />
        ) : (
          <>
            <Search setProperties={setProperties} />
            <PropertyList properties={properties} />
          </>
        )}
      </div>
    </Router>
  );
};

export default App;
