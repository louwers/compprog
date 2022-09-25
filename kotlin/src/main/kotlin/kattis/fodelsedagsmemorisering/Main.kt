// https://open.kattis.com/problems/fodelsedagsmemorisering

data class Date(val day: Int, val month: Int)

class RememberedBirthDays() {
    var birthDayMap: MutableMap<Date, Pair<Int, String>> = mutableMapOf()

    fun add(name: String, priority: Int, birthday: Date) {
        fun actuallyAdd(name: String, priority: Int, birthday: Date) {
            birthDayMap[birthday] = Pair(priority, name)
        }

        val existing = birthDayMap.get(birthday)
        if (existing == null) {
            actuallyAdd(name, priority, birthday)
            return
        }
        val (otherPriority, _) = existing
        if (otherPriority > priority) return
        actuallyAdd(name, priority, birthday)
    }

    fun numberRemembered(): Int {
        return birthDayMap.size
    }

    fun friends(): Iterable<String> {
        return birthDayMap.values.map { it.second }.sorted()
    }
}


fun main(args: Array<String>) {
    val birthdays = RememberedBirthDays()

    var numberOfFriends = readLine()!!.toInt()
    while (numberOfFriends-- != 0) {
        val line = readLine()!!.split(" ")
        val name = line[0].toString()
        val priority = line[1].toInt()
        val day = line[2].substring(0, 2).toInt()
        val month = line[2].substring(3, 5).toInt()
        birthdays.add(name, priority, Date(day, month))
    }

    println(birthdays.numberRemembered())
    birthdays.friends().forEach(::println)
}