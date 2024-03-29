import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;

public class Main {

    public static void main(String[] args) {

        int[] numbers = new int[] {2, 1, 3, 4, 5, -2, 321321};

        System.out.println("Nieposortowana tablica");

        for(int number : numbers)
            System.out.print(number + " ");

        DivideTask task = new DivideTask(numbers, 0, numbers.length);
        ForkJoinPool forkJoinPool = new ForkJoinPool();

        forkJoinPool.execute(task);
        int[] wynik = task.join();

        System.out.println();
        System.out.println("Posortowana tablica");

        for(int number : wynik)
            System.out.print(number + " ");
    }

}
