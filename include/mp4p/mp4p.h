#ifndef mp4parser_h
#define mp4parser_h

#include <stdint.h>
#include <mp4p/mp4pfile.h>
#include <mp4p/mp4patomdata.h>


typedef size_t (*mp4p_atom_data_write_func_t) (void *atom_data, uint8_t *buffer, uint32_t buffer_size);
typedef void (*mp4p_atom_data_free_func_t) (void *atom_data);

typedef struct mp4p_atom_s {
    uint64_t pos;
    uint32_t size;
    char type[4];
    void *data;
    struct mp4p_atom_s *subatoms;
    struct mp4p_atom_s *next;

    /// If `free` is not null, if will be called with the `data` passed as argument, to free the data
    mp4p_atom_data_free_func_t free;

    /// If `write` is null, data must point to a plain buffer of size-8 bytes, that can be saved directly
    mp4p_atom_data_write_func_t write;

    /// Special case for `meta` atom, which has both the common header and subatoms.
    /// For this case, the version_flags is stored in data, and is written before subatoms.
    unsigned write_data_before_subatoms : 1;
} mp4p_atom_t;


void
mp4p_atom_free (mp4p_atom_t *atom);

void
mp4p_atom_free_list (mp4p_atom_t *atom);

// Loading starts from the current position in the stream.
mp4p_atom_t *
mp4p_open (mp4p_file_callbacks_t *callbacks);

mp4p_atom_t *
mp4p_atom_find (mp4p_atom_t *root, const char *path);

uint64_t
mp4p_stts_total_num_samples (mp4p_atom_t *stts_atom);

uint32_t
mp4p_stts_sample_duration (mp4p_atom_t *stts_atom, uint32_t mp4sample);

uint32_t
mp4p_stts_mp4sample_containing_sample (mp4p_atom_t *stts_atom, uint64_t sample, uint64_t *mp4sample_startingsample);

uint64_t
mp4p_stts_total_sample_duration (mp4p_atom_t *stts_atom);

uint32_t
mp4p_sample_size (mp4p_atom_t *stsz_atom, uint32_t sample);

uint64_t
mp4p_sample_offset (mp4p_atom_t *stbl_atom, uint32_t sample);

const char *
mp4p_genre_name_for_index (uint16_t index);

void
mp4p_atom_remove_sibling(mp4p_atom_t *atom, mp4p_atom_t *sibling, int free);

void
mp4p_atom_remove_subatom (mp4p_atom_t *atom, mp4p_atom_t *subatom);

mp4p_atom_t *
mp4p_atom_new (const char *type);

mp4p_atom_t *
mp4p_atom_clone (mp4p_atom_t *src);

mp4p_atom_t *
mp4p_atom_clone_list (mp4p_atom_t *src);

uint32_t
mp4p_atom_subatom_count (mp4p_atom_t *atom);

void
mp4p_atom_update_size (mp4p_atom_t *atom);

void
mp4p_rebuild_positions (mp4p_atom_t *atom, uint64_t init_pos);

mp4p_atom_t *
mp4p_atom_insert (mp4p_atom_t *parent, mp4p_atom_t *before, mp4p_atom_t *atom);

mp4p_atom_t *
mp4p_atom_append (mp4p_atom_t *parent, mp4p_atom_t *atom);

mp4p_atom_t *
mp4p_ilst_create_genre (const char *text);

mp4p_atom_t *
mp4p_ilst_create_track_disc (const char *type, uint16_t index, uint16_t total);

mp4p_atom_t *
mp4p_ilst_create_text (const char *type, const char *text);

mp4p_atom_t *
mp4p_ilst_create_custom (const char *name, const char *text);

void
mp4p_atom_dump (mp4p_atom_t *atom);

void
mp4p_hdlr_init (mp4p_atom_t *hdlr_atom, const char *type, const char *subtype, const char *manufacturer);

/// @returns memcmp result of comparison of type and the atom's typs
int
mp4p_atom_type_compare (mp4p_atom_t *atom, const char *type);

int
mp4p_fourcc_compare (const char *value1, const char *value2);

uint32_t
mp4p_atom_to_buffer (mp4p_atom_t *atom, uint8_t *buffer, uint32_t buffer_size);

int
mp4p_update_metadata (mp4p_file_callbacks_t *callbacks, mp4p_atom_t *mp4file);

mp4p_atom_t *
mp4p_atom_meta_find_custom (mp4p_atom_t *ilst, const char *key);

int
mp4p_trak_playable (mp4p_atom_t *trak_atom);

int
mp4p_trak_has_chapters (mp4p_atom_t *trak_atom);

void
mp4p_dbg_dump_atom (mp4p_atom_t *atom);

//! Project version number for mp4p.
extern double mp4pVersionNumber;

//! Project version string for mp4p.
extern const unsigned char mp4pVersionString[];

#endif /* mp4parser_h */
