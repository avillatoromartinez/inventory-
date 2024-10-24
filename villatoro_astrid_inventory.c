/*
CSC 3320
Homework 3
Astrid Villatoro
Program: Inventory Management System
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME 50
#define MAX_DESC 100

typedef struct Product{
	char prodName[MAX_NAME]; 	//Product name
	int numUnits; 		//Number of units in stock
	float price; 
	union {
		struct {
			float l, w, h;		//Dimensions: length, width, height
		} dimensions;
		char desc[MAX_DESC]; 	//Product Description
	} details;
	struct Product *next;
} Product;

Product* getNewProduct();
void addProduct(Product **head);
void displayProducts(Product *head);
void updateProdQuant(Product *head);
void updateProdPrice(Product *head);
void deleteProduct(Product **head);
void freeList(Product *head);

int main() {
	Product *head = NULL;
	int choice;
	do {
		printf("\n\nInventory Management Service");
		printf("\n1. Add Product");
		printf("\n2. Display Products");
		printf("\n3. Update Product Quantity");
		printf("\n4. Update Product Price");
		printf("\n5. Delete Product");
		printf("\n6. Exit");
	
		printf("\n\nEnter your choice: ");
		scanf("%d", &choice);
		getchar();
		switch(choice) {
			case 1:
				addProduct(&head);
				break;
			case 2:
				displayProducts(head);
				break;
			case 3: 
				updateProdQuant(head);
				break;
			case 4:
				updateProdPrice(head);
				break;
			case 5:
				deleteProduct(&head);
			case 6:
 				printf("\nExiting...");
				break;
				freeList(head);
			default: 	
				printf("Invalid Input\n");
		}
	}
	while(choice != 6);
	
	return 0;
}

Product* getNewProduct() {
	Product *newProduct = (Product*)malloc(sizeof(Product));
	if(newProduct == NULL) {
		exit(EXIT_FAILURE);
	}
	newProduct->next = NULL;
	return newProduct;
}

void addProduct (Product **head) {
	Product *newProduct = getNewProduct();
	printf("Enter product name: ");
        fgets(newProduct->prodName, MAX_NAME, stdin);
	strtok(newProduct->prodName, "\n");
        printf("Enter quantity: ");
        scanf("%d", &newProduct->numUnits);
	getchar();
        printf("Enter price: ");
        scanf("%f", &newProduct->price);
	getchar();
	int choice; 	//yes or no to dimensions question
        do {
            	printf("Does this product have dimensions (0 - No, 1 - Yes): ");
                scanf("%d", &choice);
		getchar();
                if(choice != 0 && choice != 1) 
                        printf("Invalid Input. Try again.\n");
                
        }
	while(choice != 0 && choice != 1);
	if(choice == 0) {		//for product description
		printf("Enter product description: ");
		fgets(newProduct->details.desc, MAX_DESC, stdin);
		strtok(newProduct->details.desc, "\n");
        }	
        else {				//for product dimensions
                printf("Enter length , width, and height (ex: 1 2 3): ");
                scanf("%f %f %f", &newProduct->details.dimensions.l, &newProduct->details.dimensions.w, &newProduct->details.dimensions.h);
                getchar();
	}
	if(*head == NULL) {
		*head = newProduct;
	}
	else {
		Product *temp = *head;
		while(temp->next != NULL) 
			temp = temp->next;
		temp->next = newProduct;
	}
	printf("Product added successfully!");
}

void displayProducts(Product *head) {
	if(head == NULL) {		//if user hasn't added anything 
		printf("Currently unavaible");
		return;
	}
	Product *current = head;
	//display
	printf("\n%-20s %-10s %-10s\n", "Name", "Quantity", "Price"); 	//format of display
	while(current != NULL) {
		printf("%-20s %-10d %-10.2f \n", current->prodName, current->numUnits, current->price);
			if(strlen(current->details.desc) > 0) {		//prints description if there was one for the item
				printf("\n	Details: %s\n", current->details.desc);
			}
			else {					//prints dimensions if there was no description
				printf("\n	Details: %.2f x %.2f x %.2f\n", current->details.dimensions.l, current->details.dimensions.w, current->details.dimensions.h);
			}
		current = current->next;
	}
}

void updateProdQuant(Product *head) {
	if(head == NULL) {		//if user hasn't added anything
		printf("Currently unavailable");
		return;
	}
	char updatedName[MAX_NAME]; //product name to update
	printf("Enter product name to update product quantity: ");
	fgets(updatedName, MAX_NAME, stdin);
	strtok(updatedName, "\n");
	Product *current = head;
	while(current != NULL) {
		if(strcmp(current->prodName, updatedName) == 0) {
			printf("Enter new quantity: ");
			scanf("%d", &current->numUnits);
			getchar();
			printf("Product quanitity updated successfully!");
			return;
		}
		current = current->next;
	}	
	printf("Product not found.\n");
}

void updateProdPrice(Product *head) {
	if(head == NULL) {
		printf("Currently unavailable");
		return;
	}
	char updatedName[MAX_NAME]; //product name to update
	printf("Enter product name to update product price: ");
	fgets(updatedName, MAX_NAME, stdin);
	strtok(updatedName, "\n");
	Product *current = head;
	while(current != NULL) {
		if(strcmp(current->prodName, updatedName) == 0) {
			printf("Enter new price: ");
			scanf("%f", &current->price);
			getchar();
			printf("Product price updated successfully!");
			return;
		}
		current = current->next;
	}
	printf("Product not found\n");
}	

void deleteProduct(Product **head) {
	if(*head == NULL) {
		printf("Currently unavailable");
		return;
	}
	char deleteProd[MAX_NAME]; //product to be deleted
	printf("Enter product name to delete: ");
	fgets(deleteProd, MAX_NAME, stdin);
	strtok(deleteProd, "\n");
	Product *temp = *head;
	Product *prev = NULL;
	while(temp != NULL) {
		if(strcmp(temp->prodName, deleteProd) == 0) {
			if(prev == NULL) {
				*head = temp->next;
			}
			else {
				prev->next = temp->next;
			}
			free(temp);
			printf("Product deleted successfully!");
			return;
		}
	prev = temp;
	temp = temp->next;
	} 
	printf("Product not found\n");
}

void freeList(Product *head) {
	Product *temp; 
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
