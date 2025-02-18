((org-mode . ((eval . (add-hook 'after-save-hook
                                (lambda nil
                                  (when
                                      (string-equal
                                       (file-name-nondirectory buffer-file-name)
                                       "README.org")
                                    (org-pandoc-export-to-gfm)))
                                nil t))))
 (nil . ((org-roam-directory . "~/workspace/fdf/roam")
         (org-roam-db-location . "~/workspace/fdf/roam/fdf.db"))))
