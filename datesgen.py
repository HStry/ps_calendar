import datetime

DAY = datetime.timedelta(days=1)


class Date(tuple):
    def __new__(cls, date):
        self = super().__new__(cls, (date.year,
                                     date.month,
                                     date.day,
                                     date.weekday(),
                                     tuple(date.isocalendar()[:2])))
        self._dt = datetime.date(self.year, self.month, self.day)
        return self
    
    @classmethod
    def now(cls):
        return cls(datetime.date.today())
    
    def __repr__(self): return f"{self.__class__.__name__}{super().__repr__()}"
    
    @property
    def year(self):     return self[0]
    @property
    def month(self):    return self[1]
    @property
    def day(self):      return self[2]
    @property
    def weekday(self):  return self[3]
    @property
    def iso(self):      return self[4]
    @property
    def isoyear(self):  return self[4][0]
    @property
    def isoweek(self):  return self[4][1]
    @property
    def datetime(self): return self._dt
    
    def __add__(self, other):
        if isinstance(other, datetime.timedelta):
            return self.__class__(self._dt + other)
        if isinstance(other, int):
            return self.__class__(self._dt + other * DAY)
        raise NotImplementedError(f"operation unsupported for '{type(other)}'")
    
    def __sub__(self, other): return self.__add__(-1 * other)


class Week(tuple):
    def __new__(cls, date):
        return super().__new__(cls, tuple(cls._iter(date)))
    
    @staticmethod
    def _iter(d):
        d = Date(d)
        d -= d.weekday
        _iso = d.iso
        while _iso == d.iso:
            yield d
            d += 1
    
    @classmethod
    def now(cls):
        return cls(datetime.date.today())
    
    def __repr__(self): return f"{self.__class__.__name__}{super().__repr__()}"
    
    @property
    def year(self):     return self[0].year
    @property
    def month(self):    return self[0].month
    @property
    def iso(self):      return self[0].iso
    @property
    def isoyear(self):  return self[0].isoyear
    @property
    def isoweek(self):  return self[0].isoweek
    
    def __add__(self, other):
        if isinstance(other, datetime.timedelta):
            return self.__class__(self[0]._dt + other)
        if isinstance(other, int):
            return self.__class__(self[0]._dt + 7 * other * DAY)
        raise NotImplementedError(f"operation unsupported for '{type(other)}'")
    
    def __sub__(self, other): return self.__add__(-1 * other)


class Year(tuple):
    def __new__(cls, year):
        return super().__new__(cls, tuple(cls._iter(year)))
    
    @staticmethod
    def _iter(y):
        w = Week(datetime.date(y, 1, 4))
        while y == w.isoyear:
            yield w
            w += 1
    
    @classmethod
    def now(cls):
        return cls(datetime.date.today().year)
    
    def __repr__(self):
        return (f"{self.__class__.__name__}({self.year}): "
                f"{self[ 0][ 0].year}-{self[ 0][ 0].month}-{self[ 0][ 0].day} - "
                f"{self[-1][-1].year}-{self[-1][-1].month}-{self[-1][-1].day}")
    
    @property
    def year(self): return self[0][0].isoyear

def hanging_indent(lines, head, tail=None):
    if isinstance(head, str):
        head = (head, ' ' * len(head))
    if isinstance(tail, str):
        tail = ('', tail)
    if tail is None:
        tail = ('', '')
    
    lines = list(lines)
    
    t = len(lines)-1
    for i, line in enumerate(lines):
        yield f"{head[bool(i)]}{line}{tail[i == t]}"


def psdict_date(date):
    if not isinstance(date, Date):
        raise TypeError(f"date must be instance of 'Date', not '{type(week)}'")
    return (f"<< /Y {date.year} "
               f"/M {date.month:>2d} "
               f"/D {date.day:>2d} "
               f"/WD {date.weekday} >>")

def psarray_week(week):
    if not isinstance(week, Week):
        raise TypeError(f"week must be instance of 'Week', not '{type(week)}'")
    
    return hanging_indent([psdict_date(day) for day in week],
                          f"[ {week[0].isoyear:>4d} {week[0].isoweek:>2d} [ ",
                          " ] ]")

def psarray_year(year):
    if not isinstance(year, Year):
        raise TypeError(f"year must be instance of 'Year', not '{type(year)}'")
    
    weeks = (psarray_week(week) for week in year)
    lines = hanging_indent((line for w in weeks for line in w), "/Weeks [ ")
    
    for line in lines:
        yield line
    yield "] def"

def psarray_out(year):
    return '\n'.join(psarray_year(year))


if __name__ == '__main__':
    import sys
    if sys.argv[1:]:
        year = Year(int(sys.argv[1]))
    else:
        year = Year.now()
    
    with open(f'weeks_{year.year}.inc', 'w', encoding='utf-8') as f:
        f.write(psarray_out(year))