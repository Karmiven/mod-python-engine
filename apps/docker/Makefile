.PHONY: build up down

# Build containers (build dependencies first)
build:
	docker compose build ac-dependencies
	docker compose build

# Start all containers
up:
	docker compose up -d

# Stop and remove all containers
down:
	docker compose down
