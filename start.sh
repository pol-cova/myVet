#!/bin/bash
# Simple script to build and run the project using Docker Compose

echo "=== Building and Starting MyVet System ==="
docker compose up --build -d
echo "=========================================="
echo "MyVet system is now starting up!"
echo "Frontend: http://localhost"
echo "Backend:  http://localhost:18080"
echo "=========================================="
echo "To view logs:   docker compose logs -f"
echo "To stop system: docker compose down"
