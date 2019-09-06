package editDistance;

public class EditDistance {

	private String firstString;

	private String secondString;

	private int firstStringLength;

	private int secondStringLength;

	private int editMatrix[][];

	public EditDistance(String firstString, String secondString) {
		super();
		this.firstString = firstString;
		this.secondString = secondString;
		this.firstStringLength = firstString.length();
		this.secondStringLength = secondString.length();
		this.editMatrix = new int[firstStringLength + 1][secondStringLength + 1];
	}

	public void calculate() {

		int i, j;
		for (i = 0; i < this.firstStringLength + 1; i++) {
			for (j = 0; j < this.secondStringLength + 1; j++) {
				if (i == 0 || j == 0) {
					this.editMatrix[i][j] = Math.max(i, j);
				} else {
					this.editMatrix[i][j] = min3(
							this.editMatrix[i - 1][j] + 1,
							this.editMatrix[i][j - 1] + 1,
							this.editMatrix[i - 1][j - 1] + (this.firstString.charAt(i - 1) != this.secondString.charAt(j - 1) ? 1 : 0));
				}
			}
		}

		System.out.println();
		System.out.println("La distanza è " + this.editMatrix[this.firstStringLength][this.secondStringLength]);
	}

	private static int min3(int a, int b, int c) {
		return (a < b ? Math.min(a, c) : Math.min(b, c));
	}
}
