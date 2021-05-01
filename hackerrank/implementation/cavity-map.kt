import java.io.*
import java.math.*
import java.security.*
import java.text.*
import java.util.*
import java.util.concurrent.*
import java.util.function.*
import java.util.regex.*
import java.util.stream.*
import kotlin.collections.*
import kotlin.comparisons.*
import kotlin.io.*
import kotlin.jvm.*
import kotlin.jvm.functions.*
import kotlin.jvm.internal.*
import kotlin.ranges.*
import kotlin.sequences.*
import kotlin.text.*

fun isSurroundedByShallowerCells(grid: Array<String>, row: Int, column: Int): Boolean {
    val currentCell = Character.getNumericValue( grid[row][column])
    val cellAbove = Character.getNumericValue( grid[row - 1][column])
    val cellBellow = Character.getNumericValue( grid[row + 1][column])
    val cellForward = Character.getNumericValue( grid[row][column + 1])
    val cellBehind = Character.getNumericValue( grid[row][column - 1])

    return currentCell > cellAbove && currentCell > cellBellow
            && currentCell > cellForward && currentCell > cellBehind

}

fun cavityMap(grid: Array<String>): Array<String> {
    if (grid.size == 1 || grid.size == 2) return grid;

    val gridSize = grid.size
    val answer = arrayOf(*grid)

    for (rowIndex in 1..gridSize-2) {
        for (columnIndex in 1..gridSize-2) {
            if (isSurroundedByShallowerCells(grid, rowIndex, columnIndex)) {
                val row = answer[rowIndex].toCharArray()
                row[columnIndex] = 'X'
                answer[rowIndex] = String(row)
            }
        }
    }

    return answer;
}

fun main(args: Array<String>) {
    val n = readLine()!!.trim().toInt()

    val grid = Array<String>(n, { "" })
    for (i in 0 until n) {
        val gridItem = readLine()!!
        grid[i] = gridItem
    }

    val result = cavityMap(grid)

    println(result.joinToString("\n"))
}
