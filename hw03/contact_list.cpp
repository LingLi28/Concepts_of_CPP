#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>


// TODO create implementation here!

/**
 * Given a contact storage, create a new contact entry by name and number.
 */
bool add(contact_list::storage& contacts, std::string_view name, contact_list::number_t number) {

	if (name == "") {
		return false;
	}

	std::vector<std::string>::iterator t;
	t = std::find(contacts.names.begin(), contacts.names.end(), name);
	if (t !=  contacts.names.end()) {
		return false;
	}
	
	contacts.numbers.push_back(number);
	contacts.names.push_back(std::string(name));
	return true;
}

/**
 * Given a contact storage, how many contacts are currently stored?
 */
size_t size(const contact_list::storage& contacts) {

	return contacts.numbers.size();
}

/**
 * Fetch a contact number from storage given a name.
 */
contact_list::number_t get_number_by_name(contact_list::storage& contacts, std::string_view name) {

	std::vector<std::string>::iterator t;
	t = std::find(contacts.names.begin(), contacts.names.end(), std::string(name));
	if (t ==  contacts.names.end()) {
		return -1;
	}
	auto pos = std::distance(t, contacts.names.begin());
	return contacts.numbers.at(pos);
}


/**
 * Return a string representing the contact list.
 */
std::string to_string(const contact_list::storage& contacts) {
	size_t size_contacts = contacts.numbers.size();
	std::string res_string{""};
	for (size_t i = 0; i < size_contacts; ++i){
		res_string = res_string + contacts.names[i] + " - " + std::to_string(contacts.numbers[i]) + "\n";
	}
	return res_string;
}


/**
 * Remove a contact by name from the contact list.
 */
bool remove(contact_list::storage& contacts, std::string_view name) {

	std::vector<std::string>::iterator t;
	t = std::find(contacts.names.begin(), contacts.names.end(), std::string(name));
	if (t ==  contacts.names.end()) {
		return false;
	}
	std::cout << "test" << std::endl;
	auto pos = std::distance(t, contacts.names.begin());

	contacts.numbers.erase(contacts.numbers.begin() + pos);
	contacts.names.erase(contacts.names.begin() + pos);
	return true;

}


bool compare(const contact_list::Person& p1, const contact_list::Person& p2) {

		return p1.name < p2.name;
};	

/**
 * Sort the contact list in-place by name.
 */
void sort(contact_list::storage& contacts) {

	size_t size_contacts = contacts.numbers.size();
	std::vector<contact_list::Person> people;
	for (size_t i = 0; i < size_contacts; ++i) {
		people.push_back({contacts.numbers[i], contacts.names[i]});
	}
	std::sort(people.begin(), people.end(), compare);

	for (size_t i = 0; i < size_contacts; ++i) {
		contacts.numbers[i] = people[i].number;
		contacts.names[i] = people[i].name;
	}

}


/**
 * Fetch a contact name from storage given a number.
 */
std::string get_name_by_number(contact_list::storage& contacts, contact_list::number_t number) {

	std::vector<contact_list::number_t>::iterator t;

	t = std::find(contacts.numbers.begin(), contacts.numbers.end(), number);
	if (t ==  contacts.numbers.end()) {
		return "";
	}

	auto pos = std::distance(t, contacts.numbers.begin());
	return contacts.names.at(pos);

}