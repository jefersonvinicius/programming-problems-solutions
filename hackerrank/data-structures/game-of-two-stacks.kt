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

fun twoStacks(maxSum: Int, a: Array<Int>, b: Array<Int>): Int {
    var currentSum = 0; var amountItemsRemoved = 0
    var aTopIdx = 0; var bTopIdx = 0;

    while (true) {

        val aIsEmpty = aTopIdx == a.size
        val bIsEmpty = bTopIdx == b.size

        if ((aIsEmpty && bIsEmpty) || (!aIsEmpty && currentSum + a[aTopIdx] > maxSum && !bIsEmpty && currentSum + b[bTopIdx] > maxSum)) break;

        if (!aIsEmpty && !bIsEmpty) {
            if (a[aTopIdx] <= b[bTopIdx]) {
                currentSum += a[aTopIdx]
                aTopIdx++
            } else {
                currentSum += b[bTopIdx]
                bTopIdx++
            }
            amountItemsRemoved++;
        } else if (aIsEmpty && currentSum + b[bTopIdx] <= maxSum) {
            currentSum += b[bTopIdx]
            amountItemsRemoved++;
            bTopIdx++
        } else if (bIsEmpty && currentSum + a[aTopIdx] <= maxSum) {
            currentSum += a[aTopIdx]
            amountItemsRemoved++;
            aTopIdx++
        } else {
            break
        }
    }

    return amountItemsRemoved;

}

fun main(args: Array<String>) {
    val g = readLine()!!.trim().toInt()

    for (gItr in 1..g) {
        val first_multiple_input = readLine()!!.trimEnd().split(" ")
        val n = first_multiple_input[0].toInt()
        val m = first_multiple_input[1].toInt()
        val maxSum = first_multiple_input[2].toInt()
        val a = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()
        val b = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()

        val result = twoStacks(maxSum, a, b)

        println(result)
    }
}
