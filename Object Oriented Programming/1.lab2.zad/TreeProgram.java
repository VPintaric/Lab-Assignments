package hr.fer.oop.lab1.topic1.prob2;

import java.lang.String;

public class TreeProgram {

	static class TreeNode {
			 
		TreeNode left;
		TreeNode right;
		String data;
		 
		 }
		 
	/**
	 * Main method
	 * @param args Program startup arguments
	 */
	public static void main(String[] args) {
		
		TreeNode node = null;
		node = insert(node, "Jasna");
		node = insert(node, "Ana");
		node = insert(node, "Ivana");
		node = insert(node, "Anamarija");
		node = insert(node, "Vesna");
		node = insert(node, "Kristina");
		
		System.out.println("Writing tree inorder: ");
		writeTree(node);
		
		//node = reverseTreeOrder(node);
		System.out.println("Writing reversed tree inorder: ");
		writeTree(node);
		
		int size = sizeOfTree(node);
		System.out.println("Number of nodes in tree is " + size + ".");
		
		boolean found = containsData(node, "Ivana");
		System.out.println("Searched element is found: " + found);
		}
	
	/**
	 * Method searches String data within the tree whose root is treeRoot
	 * @param treeRoot Root of the tree where method searches for "data"
	 * @param data String to search for within the tree
	 * @return boolean Returns "true" if there is a member that equals to "data", otherwise returns "false"
	 */
		static boolean containsData(TreeNode treeRoot, String data) {
			
			if(treeRoot == null) return false;
			
			if(treeRoot.data == data) return true;
			
			if(containsData(treeRoot.left, data) || containsData(treeRoot.right, data)) return true;
			
			return false;
		}
		 
		/**
		 * Returns amount of members in the tree with root treeRoot
		 * @param treeRoot Root of the tree
		 * @return int
		 */
		static int sizeOfTree(TreeNode treeRoot) {
			
			if(treeRoot == null) return 0;
			
			return 1 + sizeOfTree(treeRoot.left) + sizeOfTree(treeRoot.right);
		}
		
		/**
		 * Inserts a new member into a tree, member is sorted alphabetically
		 * @param treeRoot
		 * @param data
		 * @return TreeNode
		 */
		static TreeNode insert(TreeNode treeRoot, String data) {
			
			if(treeRoot == null){
				treeRoot = new TreeNode();
				treeRoot.data = data;
				treeRoot.left = null;
				treeRoot.right = null;
			}
			
			else if(treeRoot.data.compareToIgnoreCase(data) > 0) treeRoot.left = insert(treeRoot.left, data);
			else treeRoot.right = insert(treeRoot.right, data);
			
			return treeRoot;
		}
		 
		/**
		 * Write all the members of a tree in order
		 * @param treeRoot
		 */
		static void writeTree(TreeNode treeRoot) {
			if(treeRoot.left != null) writeTree(treeRoot.left);
			System.out.format("%s\n", treeRoot.data);
			if(treeRoot.right != null) writeTree(treeRoot.right);
		}
		 
		/**
		 * Reverses the order of a tree
		 * @param treeRoot
		 * @return TreeNode
		 */
		static TreeNode reverseTreeOrder(TreeNode treeRoot) {
			
			if(treeRoot != null){
				treeRoot.left = reverseTreeOrder(treeRoot.left);
				treeRoot.right = reverseTreeOrder(treeRoot.right);
				TreeNode temp = treeRoot.right;
				treeRoot.right = treeRoot.left;
				treeRoot.left = temp;
			}
			
			return treeRoot;
		}
	}