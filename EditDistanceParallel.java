package editDistance;

public class EditDistanceParallel {

	private String firstString;

	private String secondString;

	private int firstStringLength;

	private int secondStringLength;

	private int editMatrix[][];

	private int i, j;

	private int nT;

	private int chunckHeight;

	private int chunckWidth;

	public EditDistanceParallel(String firstString, String secondString, int nT) {
		super();
		this.firstString = firstString;
		this.secondString = secondString;
		this.firstStringLength = firstString.length();
		this.secondStringLength = secondString.length();
		this.editMatrix = new int[firstStringLength + 1][secondStringLength + 1];
		this.nT = nT;
	}

	private void inizialize() {

		for (i = 0; i < this.firstStringLength + 1; i++)
			this.editMatrix[i][0] = i;

		for (j = 0; j < this.secondStringLength + 1; j++)
			this.editMatrix[0][j] = j;

	}

	public void calculate() {

		inizialize();
		this.chunckHeight = this.firstStringLength / this.nT;
		this.chunckWidth = this.secondStringLength / this.nT;

		switch (this.nT) {
			case 2:

				EditThread oneTwo = new EditThread(editMatrix, 1, this.chunckHeight, 1, this.chunckWidth, firstString, secondString);
				oneTwo.start();
				while (oneTwo.isAlive()) {
				}

				EditThread twoTwo = new EditThread(editMatrix, this.chunckHeight + 1, this.firstStringLength, 1, this.chunckWidth, firstString,
						secondString);
				EditThread threeTwo = new EditThread(editMatrix, 1, this.chunckHeight, this.chunckWidth + 1, this.secondStringLength, firstString,
						secondString);
				twoTwo.start();
				threeTwo.start();
				while (oneTwo.isAlive() || twoTwo.isAlive()) {
				}

				EditThread fourTwo = new EditThread(editMatrix, this.chunckHeight + 1, this.firstStringLength, this.chunckWidth + 1,
						this.secondStringLength, firstString, secondString);
				fourTwo.start();
				while (fourTwo.isAlive()) {
				}

				break;

			case 3:

				EditThread oneThree = new EditThread(editMatrix, 1, this.chunckHeight, 1, this.chunckWidth, firstString, secondString);
				oneThree.start();
				while (oneThree.isAlive()) {
				}

				EditThread twoThree = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, 1, this.chunckWidth, firstString,
						secondString);
				EditThread threeThree = new EditThread(editMatrix, 1, this.chunckHeight, this.chunckWidth + 1, this.chunckWidth * 2, firstString,
						secondString);
				twoThree.start();
				threeThree.start();
				while (twoThree.isAlive() || threeThree.isAlive()) {
				}

				EditThread fourThree = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.firstStringLength, 1, this.chunckWidth,
						firstString,
						secondString);
				EditThread fiveThree = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, this.chunckWidth + 1,
						this.chunckWidth * 2, firstString,
						secondString);
				EditThread sixThree = new EditThread(editMatrix, 1, this.chunckHeight, (this.chunckWidth * 2) + 1, this.secondStringLength,
						firstString,
						secondString);
				fourThree.start();
				fiveThree.start();
				sixThree.start();

				while (fourThree.isAlive() || fiveThree.isAlive() || sixThree.isAlive()) {
				}

				EditThread sevenThree = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.firstStringLength, this.chunckWidth + 1,
						this.chunckWidth * 2, firstString,
						secondString);
				EditThread eightThree = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, (this.chunckWidth * 2) + 1,
						this.secondStringLength, firstString,
						secondString);
				sevenThree.start();
				eightThree.start();
				while (sevenThree.isAlive() || eightThree.isAlive()) {
				}

				EditThread nineThree = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.firstStringLength, (this.chunckWidth * 2) + 1,
						this.secondStringLength, firstString, secondString);
				nineThree.start();
				while (nineThree.isAlive()) {
				}

				break;

			case 4:

				EditThread oneFour = new EditThread(editMatrix, 1, this.chunckHeight, 1, this.chunckWidth, firstString, secondString);
				oneFour.start();
				while (oneFour.isAlive()) {
				}

				EditThread twoFour = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, 1, this.chunckWidth, firstString,
						secondString);
				EditThread threeFour = new EditThread(editMatrix, 1, this.chunckHeight, this.chunckWidth + 1, this.chunckWidth * 2, firstString,
						secondString);
				twoFour.start();
				threeFour.start();
				while (twoFour.isAlive() || threeFour.isAlive()) {
				}

				EditThread fourFour = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.chunckHeight * 3, 1, this.chunckWidth,
						firstString,
						secondString);
				EditThread fiveFour = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, this.chunckWidth + 1,
						this.chunckWidth * 2, firstString,
						secondString);
				EditThread sixFour = new EditThread(editMatrix, 1, this.chunckHeight, (this.chunckWidth * 2) + 1, this.chunckWidth * 3,
						firstString,
						secondString);
				fourFour.start();
				fiveFour.start();
				sixFour.start();

				while (fourFour.isAlive() || fiveFour.isAlive() || sixFour.isAlive()) {
				}

				EditThread sevenFour = new EditThread(editMatrix, (this.chunckHeight * 3) + 1, this.firstStringLength, 1, this.chunckWidth,
						firstString,
						secondString);
				EditThread eightFour = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.chunckHeight * 3, this.chunckWidth + 1,
						this.chunckWidth * 2, firstString,
						secondString);
				EditThread nineFour = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, (this.chunckWidth * 2) + 1,
						this.chunckWidth * 3,
						firstString,
						secondString);
				EditThread tenFour = new EditThread(editMatrix, 1, this.chunckHeight, (this.chunckWidth * 3) + 1, this.secondStringLength,
						firstString,
						secondString);
				sevenFour.start();
				eightFour.start();
				nineFour.start();
				tenFour.start();

				while (sevenFour.isAlive() || eightFour.isAlive() || nineFour.isAlive() || tenFour.isAlive()) {
				}

				EditThread elevenFour = new EditThread(editMatrix, (this.chunckHeight * 3) + 1, this.firstStringLength, this.chunckWidth + 1,
						this.chunckWidth * 2,
						firstString,
						secondString);
				EditThread twelveFour = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.chunckHeight * 3, (this.chunckWidth * 2) + 1,
						this.chunckWidth * 3, firstString,
						secondString);
				EditThread thirteenFour = new EditThread(editMatrix, this.chunckHeight + 1, this.chunckHeight * 2, (this.chunckWidth * 3) + 1,
						this.secondStringLength,
						firstString,
						secondString);
				elevenFour.start();
				twelveFour.start();
				thirteenFour.start();

				while (elevenFour.isAlive() || twelveFour.isAlive() || thirteenFour.isAlive()) {
				}

				EditThread fourteenFour = new EditThread(editMatrix, (this.chunckHeight * 3) + 1, this.firstStringLength, (this.chunckWidth * 2) + 1,
						this.chunckWidth * 3, firstString,
						secondString);
				EditThread fiveteenFour = new EditThread(editMatrix, (this.chunckHeight * 2) + 1, this.chunckHeight * 3, (this.chunckWidth * 3) + 1,
						this.secondStringLength, firstString,
						secondString);
				fourteenFour.start();
				fiveteenFour.start();
				while (fourteenFour.isAlive() || fiveteenFour.isAlive()) {
				}

				EditThread sixteenFour = new EditThread(editMatrix, (this.chunckHeight * 3) + 1, this.firstStringLength, (this.chunckWidth * 3) + 1,
						this.secondStringLength, firstString, secondString);
				sixteenFour.start();
				while (sixteenFour.isAlive()) {
				}

				break;
		}

		System.out.println();
		System.out.println("La distanza è " + this.editMatrix[this.firstStringLength][this.secondStringLength]);
	}

	public void stamp() {
		int i, j;
		for (i = 0; i < this.firstStringLength + 1; i++) {
			for (j = 0; j < this.secondStringLength + 1; j++) {
				System.out.print(this.editMatrix[i][j]);
			}
			System.out.println();
		}
	}

}
