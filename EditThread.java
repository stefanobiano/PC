package editDistance;

public class EditThread extends Thread {

	private int editMatrix[][];

	int iStart;

	int iStop;

	int jStart;

	int jStop;

	String firstString;

	String secondString;

	public EditThread(int editMatrix[][], int iStart, int iStop, int jStart, int jStop, String firstString, String secondString) {
		this.editMatrix = editMatrix;
		this.iStart = iStart;
		this.iStop = iStop;
		this.jStart = jStart;
		this.jStop = jStop;
		this.firstString = firstString;
		this.secondString = secondString;
	}

	private static int min3(int a, int b, int c) {
		return (a < b ? Math.min(a, c) : Math.min(b, c));
	}

	public void run() {
		int i, j;
		for (i = iStart; i <= iStop; i++) {
			for (j = jStart; j <= jStop; j++) {
				this.editMatrix[i][j] = min3(
						this.editMatrix[i - 1][j] + 1,
						this.editMatrix[i][j - 1] + 1,
						this.editMatrix[i - 1][j - 1] + (this.firstString.charAt(i - 1) != this.secondString.charAt(j - 1) ? 1 : 0));
			}
		}
	}

}
