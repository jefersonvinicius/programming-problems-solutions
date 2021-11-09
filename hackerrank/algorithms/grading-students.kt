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

fun gradingStudents(grades: Array<Int>): Array<Int> {
    val result = mutableListOf<Int>()
    for (grade in grades) {
        val next5Multiplier = getNext5Multiplier(grade)
        if (grade < 38 || next5Multiplier - grade >= 3) result.add(grade)
        else result.add(next5Multiplier)
    }
    return result.toTypedArray()
}

fun getNext5Multiplier(n: Int): Int {
    var next = n;
    while (next % 5 != 0) {
        next++;
    }
    return next;
}

fun main(args: Array<String>) {
    val gradesCount = readLine()!!.trim().toInt()

    val grades = Array<Int>(gradesCount, { 0 })
    for (i in 0 until gradesCount) {
        val gradesItem = readLine()!!.trim().toInt()
        grades[i] = gradesItem
    }

    val result = gradingStudents(grades)

    println(result.joinToString("\n"))
}
