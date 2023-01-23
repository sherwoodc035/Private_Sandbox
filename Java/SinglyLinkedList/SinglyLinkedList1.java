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

		System.out.println("Nodes in singly linked list: ");
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

		System.out.println("Nodes in singly linked list: ");
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
	// sort the list in ascending order
	public void sortAscend() {
		Node start = head;	// start will shift position to next node in list
		Node curr = head;	// tracks current node position
		Node prev = null;	// tracks previous node position
		Node temp = null;	// temp node to help with sorting

		// sorting loop
		while (start != tail)
		{
			System.out.println("  (start) = " + start);

			while (curr != tail)
			{
				System.out.println("    (curr) = " + curr);

				// if the next node is null, cannot do a sort here
				if (curr.next == null)
					break;
				
				if (curr.next.data < curr.data)
				{
					System.out.println("sort");
					// sort the nodes by pointing to new worlds
					// I don't undestand how to make this work...
					prev.next = curr.next;
					curr.next = curr.next.next;
				}
				// move to next node
				curr = curr.next;
			}
			start = start.next;
			curr = start;
		}
		System.out.println();
	}

	/* call main! */
	public static void main(String[] args) {
		SinglyLinkedList slist = new SinglyLinkedList();

		// add nodes
		slist.addNode(1);
		slist.addNode(3);
		slist.addNode(2);
		slist.addNode(4);
		// slist.addNode(22);
		// slist.addNode(35);
		// slist.addNode(13);
		// slist.addNode(56);

		// display nodes in list
		slist.display();
		// display nodes and addresses in list
		slist.displayAddr();
		// sort nodes in ascedning order
		System.out.println("Sorting list...");
		slist.sortAscend();
		slist.displayAddr();
	}
}