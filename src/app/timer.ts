export class Timer {
  begin: Date;
  end: Date;

  public static getDate(timer: Timer): string {
    const date = new Date(timer.begin);
    return [date.getFullYear(), date.getMonth(), date.getDate()].join('/');
  }

  public static getElapsedTime(timer: Timer): number {
    const begin = new Date(timer.begin);
    const end = new Date(timer.end);
    return end.getTime() - begin.getTime();
  }
}
