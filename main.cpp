#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include "coordinate.h"

static int global_id = 0;


//Adds coordinate to end of list
void add_coordinate(Coordinate *list_end, float x, float y) {
    Coordinate *new_coord = new Coordinate();
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = ++global_id; 
    new_coord->next = nullptr;
    new_coord->previous = list_end;

    list_end->next = new_coord;
}


//Display list forward
void fw_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning->next; 
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id << " ("
                  << current->x << ", " << current->y << ")\n";
        current = current->next;
    }
}

//Display list backward
void bw_display(Coordinate *list_end) {
    Coordinate *current = list_end;
    while (current->previous != nullptr) {
        std::cout << "ID: " << current->coord_id << " ("
                  << current->x << ", " << current->y << ")\n";
        current = current->previous;
    }
}

//Delete coordinate
void del_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
    Coordinate *current = list_beginning->next; 
    while (current != nullptr) {
        if (current->coord_id == coord_id_to_delete) {
            if (current->previous) current->previous->next = current->next;
            if (current->next) current->next->previous = current->previous;
            delete current;
            std::cout << "Coordinate ID " << coord_id_to_delete << " deleted.\n";
            return;
        }
        current = current->next;
    }
    std::cout << "Coordinate ID " << coord_id_to_delete << " not found.\n";
}

//Length of list
int list_length(Coordinate *list_beginning) {
    int length = 0;
    Coordinate *current = list_beginning->next; 
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

// Find closest coordinate
void closest_to(Coordinate *list_beginning, float x, float y) {
    Coordinate *current = list_beginning->next; 
    Coordinate *closest = nullptr;
    float min_distance = std::numeric_limits<float>::max();

    while (current != nullptr) {
        float distance = std::sqrt(std::pow(current->x - x, 2) + std::pow(current->y - y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = current;
        }
        current = current->next;
    }

    if (closest) {
        std::cout << "Closest to (" << x << ", " << y << ") is ID: "
                  << closest->coord_id << " (" << closest->x << ", "
                  << closest->y << ") with distance " << min_distance << "\n";
    } else {
        std::cout << "No coordinates in the list.\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }

    int num_coords = std::stoi(argv[1]);
    std::srand(std::time(0)); 

    Coordinate *list_head = new Coordinate();
    list_head->next = nullptr;
    list_head->previous = nullptr;

    Coordinate *list_end = list_head;
    for (int i = 0; i < num_coords; ++i) {
        float x = static_cast<float>(std::rand()) / RAND_MAX * 100;
        float y = static_cast<float>(std::rand()) / RAND_MAX * 100;
        add_coordinate(list_end, x, y);
        list_end = list_end->next;
    }

    std::cout << "Forward Display:\n";
    fw_display(list_head);

    std::cout << "\nBackward Display:\n";
    bw_display(list_end);

    if (num_coords > 0) {
        int delete_id = std::rand() % num_coords + 1;
        std::cout << "\nDeleting random coordinate with ID...\n";
        del_coordinate(list_head, delete_id);
    }

    float target_x = static_cast<float>(std::rand()) / RAND_MAX * 100;
    float target_y = static_cast<float>(std::rand()) / RAND_MAX * 100;
    std::cout << "\nRandom coordinate: (" << target_x << ", " << target_y << "):\n";
    closest_to(list_head, target_x, target_y);

    return 0;
}
