#pragma once

#include "tstring.h"

class vmsCommandLineParser
{
public:
	// first element of a pair is parameter
	// the second one is its value
	// (e.g. -string="test" --> "string", "test")
	typedef std::pair <tstring, tstring> Argument;
	typedef std::vector <Argument> tArguments;
public:
	bool Parse (LPCTSTR ptszCmdLine = GetCommandLine ())
	{
		m_vArgs.clear ();

		if (*ptszCmdLine == '"')
		{
			ptszCmdLine = _tcschr (ptszCmdLine+1, '"');
			if (ptszCmdLine)
				ptszCmdLine++;
			else
				return false;
		}
		else
		{
			while (*ptszCmdLine && *ptszCmdLine != ' ')
				ptszCmdLine++;
		}

		tstring tstrParam, tstrValue;
		tstrParam.reserve (MAX_PATH);
		tstrValue.reserve (MAX_PATH);

		while (*ptszCmdLine)
		{
			tstrParam = _T ("");
			tstrValue = _T ("");
			
			bool bHasValue = true;

			// skip spaces and CLRFs
			while (*ptszCmdLine && (*ptszCmdLine == ' ' || *ptszCmdLine == '\r' || *ptszCmdLine == '\n'))
				ptszCmdLine++;

			if (*ptszCmdLine == '/' || *ptszCmdLine == '-')
			{
				while (*++ptszCmdLine && *ptszCmdLine != ' ' && *ptszCmdLine != '=')
					tstrParam += *ptszCmdLine;

				while (*ptszCmdLine == ' ')
					ptszCmdLine++;

				// param=value ?
				if (*ptszCmdLine == '=')
				{
					ptszCmdLine++;
					while (*ptszCmdLine == ' ')
						ptszCmdLine++;
				}
				else
					bHasValue = false;
			}

			if (bHasValue)
			{
				TCHAR cSp = ' ';	// character that accomplishes parameter
				TCHAR cSp1 = '\n', cSp2 = '\r';
				// parameter is quoted ("parameter") or apostrophed ('parameter')?
				if (*ptszCmdLine == '"' || *ptszCmdLine == '\'')
				{
					cSp = *ptszCmdLine++;
					cSp1 = cSp2 = 0;
				}

				while (*ptszCmdLine && *ptszCmdLine != cSp && *ptszCmdLine != cSp1 && *ptszCmdLine != cSp2)
					tstrValue += *ptszCmdLine++;

				while (*ptszCmdLine && (*ptszCmdLine == cSp || *ptszCmdLine == cSp1 || *ptszCmdLine == cSp2))
					ptszCmdLine++;
			}

			if (!tstrParam.empty () || !tstrValue.empty ())
				m_vArgs.push_back (Argument (tstrParam, tstrValue));
		}

		return true;
	}

	size_t getArgumentCount () const {return m_vArgs.size ();}
	const Argument& getArgument (size_t nIndex) const {return m_vArgs [nIndex];}
	const tArguments& getArguments () const {return m_vArgs;}

public:
	vmsCommandLineParser (LPCTSTR ptszCmdLine = GetCommandLine ()) {Parse (ptszCmdLine);}
	const Argument* findArgument (LPCTSTR ptszName) const
	{
		for (size_t i = 0; i < m_vArgs.size (); i++)
		{
			if (m_vArgs [i].first == ptszName)
				return &m_vArgs [i];
		}
		return NULL;
	}
	// case independent (CI) version
	tArguments::const_iterator findArgumentCI (LPCTSTR ptszName) const
	{
		for (tArguments::const_iterator it = m_vArgs.cbegin (); it != m_vArgs.cend (); ++it)
		{
			if (!_tcsicmp (it->first.c_str (), ptszName))
				return it;
		}
		return m_vArgs.end ();
	}

protected:
	tArguments m_vArgs;
};