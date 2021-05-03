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

class Stack {
    private lateinit var items: MutableList<Int>;
    var totalHeight = 0;

    constructor(initialItems: Array<Int>) {
        items = mutableListOf(*initialItems)
        for (item in initialItems) {
            totalHeight += item
        }
    }

    fun pop(): Int {
        if (items.size == 0) return -1
        val itemTop = items[0]
        items.removeAt(0)
        totalHeight -= itemTop
        return itemTop
    }

    companion object {
        fun getStackWithBiggerHeight(s1: Stack, s2: Stack, s3: Stack): Stack {
            if (s1.totalHeight >= s2.totalHeight && s1.totalHeight >= s3.totalHeight) return s1;
            if (s2.totalHeight >= s1.totalHeight && s2.totalHeight >= s3.totalHeight) return s2;
            return s3;
        }
    }
}

fun equalStacks(h1: Array<Int>, h2: Array<Int>, h3: Array<Int>): Int {
    val stack1 = Stack(h1)
    val stack2 = Stack(h2)
    val stack3 = Stack(h3)

    while (true) {
        if (stack1.totalHeight == stack2.totalHeight && stack1.totalHeight == stack3.totalHeight) break;
        val stack = Stack.getStackWithBiggerHeight(stack1, stack2, stack3);
        if (stack.pop() == -1) return 0;
    }

    return stack1.totalHeight
}

fun main(args: Array<String>) {
    val first_multiple_input = readLine()!!.trimEnd().split(" ")

    val n1 = first_multiple_input[0].toInt()

    val n2 = first_multiple_input[1].toInt()

    val n3 = first_multiple_input[2].toInt()

    val h1 = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()

    val h2 = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()

    val h3 = readLine()!!.trimEnd().split(" ").map{ it.toInt() }.toTypedArray()

    val result = equalStacks(h1, h2, h3)

    println(result)
}
