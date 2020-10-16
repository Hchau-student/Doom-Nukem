//
// Created by Hugor Chau on 10/16/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/level_editor.h"

void		create_new_file(char *filename)
{
	char					*full_name;

	full_name = ft_strjoin("touch ", filename);
	system(full_name);
	ft_strdel(&full_name);
	full_name = ft_strjoin("chmod 777 ", filename);
	system(full_name);
	ft_strdel(&full_name);
}
