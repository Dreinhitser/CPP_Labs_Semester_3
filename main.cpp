#include <iostream>
#include <stdexcept>

class Time
{
private:
	int hours_;
	int minutes_;
	int seconds_;

	const int hoursDivider = 24;
	const int minutesDivider = 60;
	const int secondsDivider = 60;
public:
	Time()
	{
		hours_ = 0;
		minutes_ = 0;
		seconds_ = 0;
	}

	Time(const Time& time)
	{
		hours_ = time.hours_;
		minutes_ = time.minutes_;
		seconds_ = time.seconds_;
	}

	Time(const int hours, const int minutes, const int seconds)
	{
		hours_ = hours;
		minutes_ = minutes;
		seconds_ = seconds;
	}

	void printTime()
	{
		std::cout << hours_ << ":" << minutes_ << ":" << seconds_ <<
			std::endl;
	}

	void setTime(const int hours, const int minutes, const int seconds)
	{
		try
		{
			if (hours < 0 || hours >= hoursDivider ||
				minutes < 0 || minutes >= minutesDivider ||
				seconds < 0 || seconds >= secondsDivider)
			{
				throw std::runtime_error("invalid value");
			}
			hours_ = hours;
			minutes_ = minutes;
			seconds_ = seconds;
		}
		catch (std::exception& exception)
		{
			std::cerr << "Error: " << exception.what() << std::endl;
			exit(EXIT_FAILURE);
		}

	}

	int getHours() { return hours_; }
	int getMinutes() { return minutes_; }
	int getSeconds() { return seconds_; }

	Time& operator=(const Time& time)
	{
		if (&time == this)
			return *this;

		hours_ = time.hours_;
		minutes_ = time.minutes_;
		seconds_ = time.seconds_;

		return *this;
	}

	Time& operator+=(const Time time)
	{
		minutes_ += (seconds_ + time.seconds_) / secondsDivider;
		seconds_ = (seconds_ + time.seconds_) % secondsDivider;
		
		hours_ += (minutes_ + time.minutes_) / minutesDivider;
		minutes_ = (minutes_ + time.minutes_) % minutesDivider;

		hours_ = (hours_ + time.hours_) % hoursDivider;

		return *this;
	}

	Time& operator-=(const Time& time)
	{
		seconds_ -= time.seconds_;
		if (seconds_ < 0)
		{
			seconds_ *= -1;
			minutes_ -= 1;
		}
		seconds_ = secondsDivider - seconds_;

		minutes_ -= time.minutes_;
		if (minutes_ < 0)
		{
			minutes_ *= -1;
			hours_ -= 1;
		}
		minutes_ = minutesDivider - minutes_;

		hours_ -= time.hours_;
		if (hours_ < 0)
		{
			hours_ *= -1;
		}
		hours_ = hoursDivider - hours_;

		return *this;
	}
	
	friend Time operator+(const Time& time1, const Time& time2);
	friend Time operator-(const Time& time1, const Time& time2);

	friend bool operator==(const Time& time1, const Time& time2);
	friend bool operator!=(const Time& time1, const Time& time2);

	friend bool operator>(const Time& time1, const Time& time2);
	friend bool operator>=(const Time& time1, const Time& time2);

	friend bool operator<(const Time& time1, const Time& time2);
	friend bool operator<=(const Time& time1, const Time& time2);
};

Time operator+(const Time& time1, const Time& time2)
{
	Time timeResult;

	timeResult.seconds_ = (time1.seconds_ + time2.seconds_) %
		timeResult.secondsDivider;
	timeResult.minutes_ += (time1.seconds_ + time2.seconds_) /
		timeResult.secondsDivider;

	timeResult.minutes_ += (time1.minutes_ + time2.minutes_) %
		timeResult.minutesDivider;
	timeResult.hours_ += (time1.minutes_ + time2.minutes_) /
		timeResult.minutesDivider;

	timeResult.hours_ += (time1.hours_ + time2.hours_) %
		timeResult.hoursDivider;

	return timeResult;
}

Time operator-(const Time& time1, const Time& time2)
{
	Time timeResult;

	timeResult.seconds_ = time1.seconds_ - time2.seconds_;
	if (timeResult.seconds_ < 0)
	{
		timeResult.seconds_ *= -1;
		timeResult.minutes_ -= 1;
	}
	timeResult.seconds_ = timeResult.secondsDivider - timeResult.seconds_;

	timeResult.minutes_ += time1.minutes_ - time2.minutes_;
	if (timeResult.minutes_ < 0)
	{
		timeResult.minutes_ *= -1;
		timeResult.hours_ -= 1;
	}
	timeResult.minutes_ = timeResult.minutesDivider - timeResult.minutes_;

	timeResult.hours_ += time1.hours_ - time2.hours_;
	if (timeResult.hours_ < 0)
	{
		timeResult.hours_ *= -1;
	}
	timeResult.hours_ = timeResult.hoursDivider - timeResult.hours_;

	return timeResult;
}

bool operator==(const Time& time1, const Time& time2)
{
	if (time1.hours_ == time2.hours_ &&
		time1.minutes_ == time2.minutes_ &&
		time1.seconds_ == time2.seconds_)
		return true;
	else
		return false;
}

bool operator!=(const Time& time1, const Time& time2)
{
	if (time1.hours_ != time2.hours_ &&
		time1.minutes_ != time2.minutes_ &&
		time1.seconds_ != time2.seconds_)
		return true;
	else
		return false;
}

bool operator>(const Time& time1, const Time& time2)
{
	if (time1.hours_ > time2.hours_)
		return true;
	else if (time1.hours_ < time2.hours_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ > time2.minutes_)
		return true;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ < time2.minutes_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ == time2.minutes_ &&
		time1.seconds_ > time2.seconds_)
		return true;
	else
		return false;
}

bool operator>=(const Time& time1, const Time& time2)
{
	if (time1.hours_ > time2.hours_)
		return true;
	else if (time1.hours_ < time2.hours_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ > time2.minutes_)
		return true;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ < time2.minutes_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ == time2.minutes_ &&
		time1.seconds_ >= time2.seconds_)
		return true;
	else
		return false;
}

bool operator<(const Time& time1, const Time& time2)
{
	if (time1.hours_ < time2.hours_)
		return true;
	else if (time1.hours_ > time2.hours_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ < time2.minutes_)
		return true;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ > time2.minutes_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ == time2.minutes_ &&
		time1.seconds_ < time2.seconds_)
		return true;
	else
		return false;
}

bool operator<=(const Time& time1, const Time& time2)
{
	if (time1.hours_ < time2.hours_)
		return true;
	else if (time1.hours_ > time2.hours_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ < time2.minutes_)
		return true;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ > time2.minutes_)
		return false;
	else if (time1.hours_ == time2.hours_ &&
		time1.minutes_ == time2.minutes_ &&
		time1.seconds_ <= time2.seconds_)
		return true;
	else
		return false;
}

int main()
{
	

	return 0;
}
