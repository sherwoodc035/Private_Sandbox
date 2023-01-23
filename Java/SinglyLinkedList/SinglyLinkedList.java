/*
Tutorial found at https://www.javatpoint.com/java-program-to-create-and-display-a-singly-linked-list
*/

public class SinglyLinkedList {
	// represents a node of the singly linked list
	class Node {
		int data;
		Node next;

		public Node(int data) {
			this.data = data;
			this.next = null;
		}

		/* new function! */
		// public void addr() {
		// 	System.out.println(this);
		// }
	}

	// represents the head an dtail of the list
	public Node head = null;
	public Node tail = null;

	// addNode() will add a new node to list
	public void addNode(int data) {
		// create new node
		Node newNode = new Node(data);

		// check if list is empty
		if (head == null)
		{
			// if list is empty, both head and tail will point to new node
			head = newNode;
			tail = newNode;
		}
		else
		{
			// new node will be added after tail, then change tail to new node
			tail.next = newNode;
			// new node becomes new tail of the list
			tail = newNode;
		}
	}

	// display() will display all the nodes present in the list
	public void display() {
		// point current node to head
		Node curr = head;

		if (head == null)
		{
			System.out.println("List is empty.");
			return;
		}

		System.out.println(this.size() + " nodes in singly linked list: ");
		while (curr != null)
		{
			// print each node by incrementing pointer
			System.out.print(curr.data + "  ");
			curr = curr.next;
		}
		System.out.println();
	}

	/* new function! */
	// displayAddr() will display all the nodes (and addresses) present in the list
	public void displayAddr() {
		// point current node to head
		Node curr = head;

		if (head == null)
		{
			System.out.println("List is empty.");
			return;
		}

		System.out.println(this.size() + " odes in singly linked list: ");
		while (curr != null)
		{
			// print each node by incrementing pointer
			System.out.print(curr.data + "  (" + curr + ")");
			if (curr == head)
				System.out.print(" (head)");
			else if (curr == tail)
				System.out.print(" (tail)");
			System.out.println();
			curr = curr.next;
		}
		System.out.println();
	}

	/* new function! */
	// returns the number of nodes in the list
	public int size() {
		Node curr = null;
		int n = 0;
		if (head == null)
			return 0;
		else
		{
			curr = head;
			while (curr != null)
			{
				n++;
				curr = curr.next;
			}
		}
		return n;
	}

	/* new function! */
	// sort the list in ascending order
	public void sortAscend() {
		Node curr = head;	// tracks current node position
		Node prev = null;
		Node temp = null;	// temporary node for sorting
		int i = 0;

		// sorting loop
		// if list has no nodes
		if (curr == null)
		{
			System.out.println("List is empty.");
			return;
		}
		while (start != tail)
		{
			System.out.println("List only has one node.");
			return;
		}

		while (curr != null)
		{
			if (curr.next.data < curr.data)
			{
				System.out.print("x");
				temp = curr;
				temp.next = curr.next.next;
				prev.next = temp;
				curr.next.next = curr;
				curr.next = prev.next;
			}
			else
				System.out.print("o");
			prev = curr;
			curr = curr.next;
		}
		return;
	}

	/* call main! */
	public static void main(String[] args) {
		SinglyLinkedList slist = new SinglyLinkedList();

		// add nodes
		slist.addNode(1);
		slist.addNode(2);
		slist.addNode(3);
		slist.addNode(5);
		slist.addNode(4);
		slist.addNode(6);
		slist.addNode(7);
		slist.addNode(8);
		slist.addNode(9);

		// display nodes in list
		slist.display();
		// sort nodes in ascedning order
		System.out.println("Sorting list...");
		slist.sortAscend();
		slist.display();
	}
}