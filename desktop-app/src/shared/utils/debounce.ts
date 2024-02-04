let timeout: NodeJS.Timeout | null = null;

export default function debounce<T extends (...args: any[]) => any>(
  fn: T,
  delay: number
): T {
  return ((...args: any[]) => {
    if (timeout) {
      clearTimeout(timeout);
    }

    timeout = setTimeout(() => {
      fn(...args);
    }, delay);
  }) as T;
}
