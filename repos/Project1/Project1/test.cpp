template<class T>
T SLinkedList<T>::get(int index) {
	/* Give the data of the element at given index in the list. */
	if (index >= count) {
		return tail->data;
	}
	else {
		int pos = 0;
		Node* p = this->head;
		while (pos < index) {
			pos++;
			p = p->next;
		}
		return p->data;
	}
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
	/* Assign new value for element at given index in the list */
	if (index >= count) {
		return tail->data;
	}
	else {
		int pos = 0;
		Node* p = this->head;
		while (pos < index) {
			pos++;
			p = p->next;
		}
		p->data = e;
	}
}

template<class T>
bool SLinkedList<T>::empty() {
	/* Check if the list is empty or not. */
	return !count;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
	/* Return the first index wheter item appears in list, otherwise return -1 */
	int pos = 0;
	Node* p = this->head;
	while (p != NULL) {
		if (p->data == item) return pos;
		pos++;
		p = p->next;
	}
	return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
	/* Check if item appears in the list */
	Node* p = this->head;
	while (p != NULL) {
		if (p->data == item) return true;
		p = p->next;
	}
	return false;
}